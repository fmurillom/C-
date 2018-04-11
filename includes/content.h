//
// Created by fmurillom on 06/04/18.
//

#ifndef MSERVER_CONTENT_H
#define MSERVER_CONTENT_H

#include "memBlock.h"
#include <cppcms/view.h>

namespace content {
    struct message : cppcms::base_content{
        memBlock mServer;
    };
}

#endif //MSERVER_CONTENT_H
