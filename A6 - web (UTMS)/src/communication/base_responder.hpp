#ifndef BASE_RESPONDER_HPP_INCLUDE
#define BASE_RESPONDER_HPP_INCLUDE

class BaseResponder {
public:
    virtual void ok() = 0;
    virtual void empty() = 0;
    virtual void notFound() = 0;
    virtual void badRequest() = 0;
    virtual void permissionDenied() = 0;
};

#endif // BASE_RESPONDER_HPP_INCLUDE
