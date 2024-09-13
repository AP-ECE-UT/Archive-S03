#include "member.hpp"

#include <string>
#include <vector>

#include "../../exceptions/exceptions.hpp"
#include "../../general/io_utils.hpp"
#include "../notification/notification.hpp"
#include "../shared_area/post.hpp"
#include "../shared_area/shared_area.hpp"
#include "member_consts.hpp"

using namespace member_consts;

Member::Member(std::string id, std::string name, std::string password) {
    id_ = id;
    name_ = name;
    password_ = password;
    profilePhotoAddress_ = "";
    personalPage_ = new SharedArea();
}

void Member::setProfile(std::string photoAddress) {
    profilePhotoAddress_ = photoAddress;
}

void Member::addPost(std::string title, std::string message, Member*) {
    personalPage_->addPost(title, message, this);
}

void Member::addPost(std::string title, std::string message, Member*,
                     std::string image) {
    personalPage_->addPost(title, message, image, this);
}

void Member::deletePost(unsigned int postId, Member*) {
    personalPage_->deletePost(postId);
}

std::vector<std::string> Member::getContentSummary(Member*) {
    std::vector<std::string> summary = personalPage_->getSummary();
    summary.insert(summary.begin(), this->getInformationStr());
    return summary;
}

std::string Member::getPostDetail(unsigned int postId, Member*) {
    std::string postDetail = getInformationStr() + "\n";
    postDetail += personalPage_->getPostById(postId)->getDetail();
    return postDetail;
}

void Member::connectTo(Member* member) { connections_.push_back(member); }

std::vector<Notification> Member::getNotifications() {
    std::vector<Notification> notifs;
    for (Notification* notif : notifications_) {
        notifs.push_back(*notif);
        notif->read();
    }
    notifications_.clear();
    return notifs;
}

void Member::notifyYourConnections(Notification* notification) {
    for (Member* member : connections_) {
        notification->sent();
        member->getNotified(notification);
    }
}

void Member::getNotified(Notification* notification) {
    notifications_.insert(notifications_.begin(), notification);
}

bool Member::isPassword(std::string password) { return password_ == password; }

std::string Member::getId() { return id_; }

std::string Member::getName() { return name_; }

Member* Member::findById(const std::vector<Member*>& members, std::string id) {
    if (!io_utils::isNumber(id))
        throw BadRequestException();
    for (Member* member : members) {
        if (id == member->id_)
            return member;
    }
    throw NotFoundException(messages::CAN_NOT_FIND_MEMBER);
}

Member::~Member() {
    delete personalPage_;
    for (Notification* notif : notifications_) {
        delete notif;
    }
}

Post* Member::getPostById(unsigned int postId) {
    return personalPage_->getPostById(postId);
}

bool Member::isAlreadyConnected(Member* member) {
    for (auto connection : connections_) {
        if (connection == member) {
            return true;
        }
    }
    return false;
}
