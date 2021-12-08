#include "context.h"

context::context() : ctx_(CONTEXT_ACTIVE) {
}

bool context::done() {
    ctx_mutex_.lock();
    context_state local_state = ctx_;
    ctx_mutex_.unlock();
    return local_state == CONTEXT_CANCELED;
}

void context::cancel() {
    ctx_mutex_.lock();
    ctx_ = CONTEXT_CANCELED;
    ctx_mutex_.unlock();
}