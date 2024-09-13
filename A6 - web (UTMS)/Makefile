APP_NAME=utgram

CC=g++
C_FLAGS=-std=c++20 -Wall -Wextra

OBJECTS_DIR=lib
SRC_DIR=src

SRCS=$(shell find ${SRC_DIR} -type f \( -name "*.cpp" \))
HEADERS=$(shell find ${SRC_DIR} -type f \( -name "*.hpp" \))
OBJECTS=$(patsubst $(SRC_DIR)/%.cpp, $(OBJECTS_DIR)/%.o, ${SRCS})

MAJORS_PATH   = './csv/majors.csv'
COURSES_PATH  = './csv/courses.csv'
STUDENTS_PATH = './csv/students.csv'
TEACHERS_PATH = './csv/teachers.csv'

$(APP_NAME): $(OBJECTS)
	$(CC) $(C_FLAGS) $^ -o ${APP_NAME}

run: $(APP_NAME)
	./$(APP_NAME) $(MAJORS_PATH) $(STUDENTS_PATH) $(COURSES_PATH) $(TEACHERS_PATH)

$(OBJECTS): $(HEADERS) | $(OBJECTS_DIR)

$(OBJECTS_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(C_FLAGS) -c $< -o $@

$(OBJECTS_DIR):
	cp $(SRC_DIR) $(OBJECTS_DIR) -r
	find $(OBJECTS_DIR) -type f \( -name "*.cpp" -o -name "*.hpp" \) -exec rm {} \;

clean:
	rm -rf lib ${APP_NAME}

format:
	find . -type f \( -name '*.cpp' -or -name '*.hpp' \) -exec clang-format -i {} +

test: $(APP_NAME)
	./test.sh
