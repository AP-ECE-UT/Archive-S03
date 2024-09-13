#include "post.hpp"

#include <string>
#include <vector>

#include "../../exceptions/exceptions.hpp"
#include "../member/member.hpp"
#include "shared_area_consts.hpp"

using namespace shared_area_consts;

Post::Post(unsigned int id, std::string title, std::string message,
           Member* publisher) {
    id_ = id;
    title_ = title;
    message_ = message;
    image_ = "";
    publisher_ = publisher;
}

Post::Post(unsigned int id, std::string title, std::string message,
           std::string image, Member* publisher) {
    id_ = id;
    title_ = title;
    message_ = message;
    image_ = image;
    publisher_ = publisher;
}

Post::Post(unsigned int id, std::string message, Member* publisher) {
    id_ = id;
    message_ = message;
    publisher_ = publisher;
}

Post::~Post() {}

std::string Post::getSummary() { return std::to_string(id_) + " " + title_; }

std::string Post::getSummaryWithName() {
    return std::to_string(id_) + " " + publisher_->getName() + " " + title_;
}

std::string Post::getDetail() { return getSummary() + " " + message_; }

std::string Post::getContent() { return title_ + " " + message_; }

Member* Post::getPublisher() { return publisher_; }

Post* Post::findById(const std::vector<Post*>& posts, unsigned int id) {
    for (Post* post : posts) {
        if (post->id_ == id)
            return post;
    }
    throw NotFoundException(messages::CAN_NOT_FIND_POST);
}

unsigned int Post::getIndexById(const std::vector<Post*>& posts,
                                unsigned int id) {
    for (int i = 0; i < (int)posts.size(); i++) {
        if (posts[i]->id_ == id)
            return i;
    }
    throw NotFoundException(messages::CAN_NOT_FIND_POST);
}

bool Post::isTAform() {
    return false;
}
