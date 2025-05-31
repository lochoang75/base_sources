#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <blogger.h>
#include <signal_handler.h>

static int local_variable = 0;

uint64_t virt_to_phys(void *virt_addr) {
    uint64_t virt_pfn, phys_pfn, page_offset, phys_addr;
    uint64_t entry;
    int pagemap_fd;
    long page_size = sysconf(_SC_PAGESIZE);

    pagemap_fd = open("/proc/self/pagemap", O_RDONLY);
    if (pagemap_fd < 0) {
        BLOG(LOG_ERR, "open pagemap");
        return 0;
    }

    virt_pfn = (uint64_t)virt_addr / page_size;
    off_t offset = virt_pfn * sizeof(uint64_t);

    if (lseek(pagemap_fd, offset, SEEK_SET) == (off_t)-1) {
        BLOG(LOG_ERR, "lseek pagemap");
        close(pagemap_fd);
        return 0;
    }

    if (read(pagemap_fd, &entry, sizeof(entry)) != sizeof(entry)) {
        BLOG(LOG_ERR, "read pagemap");
        close(pagemap_fd);
        return 0;
    }

    close(pagemap_fd);

    if (!(entry & (1ULL << 63))) {
        // Page not present
        return 0;
    }

    phys_pfn = entry & ((1ULL << 55) - 1);
    page_offset = (uint64_t)virt_addr % page_size;
    phys_addr = (phys_pfn * page_size) + page_offset;
    return phys_addr;
}

int main(int argc __attribute__((unused)), char **argv)
{
    blog_init(LOG_INFO, argv[0]);
    signal_handler_init();
    uint64_t physic_address = virt_to_phys(&local_variable);
    BLOG(LOG_INFO, "Virtual address %ld map to physical address %ld", &local_variable, physic_address);
    return 0;
}