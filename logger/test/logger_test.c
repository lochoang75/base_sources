#include "blogger.h"

int main(int argc __attribute__((unused)), char **argv)
{
    blog_init(LOG_INFO, argv[0]);
    BLOG_INFO("This is info log");
    BLOG_DEBUG("This is debug log");
    BLOG_WARN("This is warning log");
    BLOG_ERR("This is error log");
    BLOG_NOTICE("This is notice log");
    BLOG_EMERG("This is emerge log");
    return 0;
}
