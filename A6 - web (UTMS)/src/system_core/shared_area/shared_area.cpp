#include "shared_area.hpp"

#include <string>
#include <vector>

#include "../../exceptions/exceptions.hpp"
#include "../member/member.hpp"
#include "../member/professor.hpp"
#include "TAform.hpp"
#include "post.hpp"

SharedArea::SharedArea() { nextPostId_ = 1; }

SharedArea::~SharedArea() {
    for (auto post : posts_)
        delete post;
}

void SharedArea::addPost(std::string title, std::string message,
                         Member* publisher) {
    Post* newPost = new Post(nextPostId_, title, message, publisher);
    nextPostId_++;
    posts_.insert(posts_.begin(), newPost);
}

void SharedArea::addPost(std::string title, std::string message,
                         std::string image, Member* publisher) {
    Post* newPost = new Post(nextPostId_, title, message, image, publisher);
    nextPostId_++;
    posts_.insert(posts_.begin(), newPost);
}

void SharedArea::addTAForm(Presentation* coursePresentation,
                           std::string message, Member* publisher) {
    Post* newPost =
        new TAform(nextPostId_, message, publisher, coursePresentation);
    nextPostId_++;
    posts_.insert(posts_.begin(), newPost);
}

void SharedArea::deletePost(unsigned int id) {
    unsigned int index = Post::getIndexById(posts_, id);
    Post* targetPost = Post::findById(posts_, id);
    posts_.erase(posts_.begin() + index);
    delete targetPost;
}

std::vector<std::string> SharedArea::getSummary() {
    std::vector<std::string> summary;
    for (Post* post : posts_) {
        summary.push_back(post->getSummary());
    }
    return summary;
}

std::vector<std::string> SharedArea::getSummaryWithName() {
    std::vector<std::string> summary;
    for (Post* post : posts_) {
        summary.push_back(post->getSummaryWithName());
    }
    return summary;
}

Post* SharedArea::getPostById(unsigned int id) {
    return Post::findById(posts_, id);
}

std::string SharedArea::getPostDetail(unsigned int postId) {
    return getPostById(postId)->getDetail();
}

void SharedArea::addStudentToTAForm(Member* student, unsigned int formId) {
    Post* post = getPostById(formId);
    TAform* taForm = dynamic_cast<TAform*>(post);
    taForm->addStudentToTAForm(student);
}

void SharedArea::closeTAForm(unsigned int formId, std::vector<bool> results) {
    Post* post = getPostById(formId);
    TAform* taForm = dynamic_cast<TAform*>(post);
    if (taForm == nullptr)
        throw NotFoundException();
    taForm->sendRequestResults(results);
    Professor* professor = dynamic_cast<Professor*>(taForm->getPublisher());
    professor->addAssistantsToPresentation(taForm, results);
    this->deletePost(formId);
}

std::vector<std::string>
SharedArea::collectStudentInfoForTAForm(unsigned int formId) {
    Post* post = getPostById(formId);
    TAform* taForm = dynamic_cast<TAform*>(post);
    return taForm->studentInfos();
}
