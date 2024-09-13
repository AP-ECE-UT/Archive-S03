#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

constexpr int INITIAL_BALANCE = 0;

struct User {
    std::string name;
    float balance;
};

struct Settlement {
    std::string from;
    std::string to;
    float amount;
};

enum class ExpenseType {
    equally,
    unequally,
    adjustment,
};

struct Expense {
    ExpenseType type;
    std::vector<User> payers;
    std::vector<User> borrowers;
};

std::vector<User> read_users(const std::string& users_file_path) {
    std::ifstream users_file(users_file_path);
    std::vector<User> users;
    std::string user_name;
    std::getline(users_file, user_name);
    while (std::getline(users_file, user_name)) {
        User user;
        user.name = user_name;
        user.balance = INITIAL_BALANCE;
        users.push_back(user);
    }
    return users;
}

std::vector<std::string> split_string(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream sstr(str);
    while (std::getline(sstr, token, delimiter)) {
        tokens.push_back(std::move(token));
    }
    return tokens;
}

std::vector<User> read_debt_data(const std::string& debt_data) {
    std::vector<User> users;
    std::vector<std::string> users_data = split_string(debt_data, ';');
    for (const auto& user_data : users_data) {
        std::vector<std::string> user_data_splitted = split_string(user_data, ':');
        User user;
        user.name = user_data_splitted[0];
        if (user_data_splitted.size() > 1)
            user.balance = std::stof(user_data_splitted[1]);
        else
            user.balance = INITIAL_BALANCE;
        users.push_back(user);
    }
    return users;
}

Expense parse_expense(const std::string& line) {
    static const std::unordered_map<std::string, ExpenseType> typeMap{
        {"equally", ExpenseType::equally},
        {"unequally", ExpenseType::unequally},
        {"adjustment", ExpenseType::adjustment},
    };
    Expense expense;
    std::vector<std::string> parsed_line = split_string(line, ',');
    expense.type = typeMap.find(parsed_line[0])->second;
    expense.payers = read_debt_data(parsed_line[1]);
    if (parsed_line.size() == 3)
        expense.borrowers = read_debt_data(parsed_line[2]);
    return expense;
}

std::vector<Expense> read_expenses(std::string expenses_file_path) {
    std::ifstream expenses_file(expenses_file_path);
    std::vector<Expense> expenses;
    std::string line;
    std::getline(expenses_file, line);
    while (std::getline(expenses_file, line))
        expenses.push_back(parse_expense(line));
    return expenses;
}

void add_user_balance(std::vector<User>& users, std::string user_name, float amount) {
    for (User& user : users) {
        if (user.name == user_name) {
            user.balance += amount;
            return;
        }
    }
}

void update_payers(std::vector<User>& users, Expense expense) {
    for (User payer : expense.payers) {
        add_user_balance(users, payer.name, payer.balance);
    }
}

void update_borrowers_additional_values(std::vector<User>& users, Expense expense) {
    for (User borrower : expense.borrowers) {
        add_user_balance(users, borrower.name, -borrower.balance);
    }
}

float calc_remaining_debts(Expense expense) {
    float remaining = 0;
    for (User payer : expense.payers)
        remaining += payer.balance;
    for (User borrower : expense.borrowers)
        remaining -= borrower.balance;
    return remaining;
}

void divide_debt_equally(std::vector<User>& users, std::vector<User>& borrowers, float remaining) {
    float equal_debt = remaining / (borrowers.size());
    equal_debt = floorf(equal_debt * 100) / 100;
    float last_borrower_debt = remaining - equal_debt * (borrowers.size() - 1);
    for (unsigned i = 0; i < borrowers.size() - 1; i++) {
        add_user_balance(users, borrowers[i].name, -equal_debt);
    }
    add_user_balance(users, borrowers[borrowers.size() - 1].name, -last_borrower_debt);
}

void handle_adjustment_expense(std::vector<User>& users, Expense expense) {
    update_payers(users, expense);
    update_borrowers_additional_values(users, expense);
    float remaining = calc_remaining_debts(expense);
    divide_debt_equally(users, expense.borrowers, remaining);
}

void handle_equally_expense(std::vector<User>& users, Expense expense) {
    if (!expense.borrowers.empty()) {
        handle_adjustment_expense(users, expense);
        return;
    }
    for (const auto& user : users) {
        expense.borrowers.push_back({user.name, 0});
    }
    handle_adjustment_expense(users, expense);
}

void handle_unequally_expense(std::vector<User>& users, Expense expense) {
    handle_adjustment_expense(users, expense);
}

bool is_in_borrowers(const std::vector<User>& borrowers, User user) {
    for (User borrower : borrowers) {
        if (user.name == borrower.name)
            return true;
    }
    return false;
}

void add_remaining_borrowers(std::vector<User> users, Expense& expense) {
    for (User user : users) {
        if (!is_in_borrowers(expense.borrowers, user))
            expense.borrowers.insert(expense.borrowers.begin(), {user.name, INITIAL_BALANCE});
    }
}

void handle_expense(std::vector<User>& users, Expense expense) {
    switch (expense.type) {
    case ExpenseType::equally:
        handle_equally_expense(users, expense);
        return;
    case ExpenseType::unequally:
        handle_unequally_expense(users, expense);
        return;
    case ExpenseType::adjustment:
        add_remaining_borrowers(users, expense);
        handle_adjustment_expense(users, expense);
        return;
    }
}

bool user_comp(const User& a, const User& b) {
    return (a.balance < b.balance) ||
           (a.balance == b.balance && (((a.balance < 0) && a.name < b.name) || ((a.balance > 0) && a.name > b.name)));
}

std::vector<Settlement> calc_settlements(std::vector<User> users) {
    std::vector<Settlement> settlements;
    sort(users.begin(), users.end(), user_comp);
    int current_payer_idx = users.size() - 1;
    int current_borrower_idx = 0;
    while (current_payer_idx > current_borrower_idx) {
        float amount = std::min(users[current_payer_idx].balance, -users[current_borrower_idx].balance);

        users[current_payer_idx].balance -= amount;
        users[current_borrower_idx].balance += amount;
        Settlement settlement = {users[current_borrower_idx].name, users[current_payer_idx].name, roundf(amount * 100) / 100};
        if (users[current_payer_idx].balance == 0)
            current_payer_idx--;
        if (users[current_borrower_idx].balance == 0)
            current_borrower_idx++;
        settlements.push_back(settlement);
    }
    return settlements;
}

bool settlement_comp(const Settlement& a, const Settlement& b) {
    return (a.amount > b.amount) ||
           (a.amount == b.amount && a.from < b.from) ||
           (a.amount == b.amount && a.from == b.from && a.to < b.to);
}

void print_settlements(std::vector<Settlement> settlements) {
    sort(settlements.begin(), settlements.end(), settlement_comp);
    for (Settlement settlement : settlements)
        std::cout << settlement.from << " -> " << settlement.to << ": " << settlement.amount << std::endl;
}

void handle_expenses(std::vector<User>& users, const std::vector<Expense>& expenses) {
    for (const auto& expense : expenses)
        handle_expense(users, expense);
}

void run(const std::string& users_file_path, const std::string& expenses_file_path) {
    std::vector<User> users = read_users(users_file_path);
    std::vector<Expense> expenses = read_expenses(expenses_file_path);
    handle_expenses(users, expenses);
    std::vector<Settlement> settlements = calc_settlements(users);
    print_settlements(settlements);
}

int main(int argc, char* argv[]) {
    if (argc < 3)
        return 1;
    std::string users_file_path = argv[1];
    std::string expenses_file_path = argv[2];
    run(users_file_path, expenses_file_path);
    return 0;
}
