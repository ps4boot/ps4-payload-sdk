#pragma once

#ifndef PAYLOAD_UTILS_H
#define PAYLOAD_UTILS_H

#include "types.h"

struct auditinfo_addr {
  char useless[184];
};

struct ucred {
  uint32_t useless1;
  uint32_t cr_uid;
  uint32_t cr_ruid;
  uint32_t useless2;
  uint32_t useless3;
  uint32_t cr_rgid;
  uint32_t useless4;
  void *useless5;
  void *useless6;
  void *cr_prison;
  void *useless7;
  uint32_t useless8;
  void *useless9[2];
  void *useless10;
  struct auditinfo_addr useless11;
  uint32_t *cr_groups;
  uint32_t useless12;
};

struct filedesc {
  void *useless1[3];
  void *fd_rdir;
  void *fd_jdir;
};

struct proc {
  char useless[64];
  struct ucred *p_ucred;
  struct filedesc *p_fd;
};

struct thread {
  void *useless;
  struct proc *td_proc;
};

struct kpayload_kbase_info {
  uint16_t fw_version;
  uint64_t uaddr;
};

struct kpayload_kbase_args {
  void *syscall_handler;
  struct kpayload_kbase_info *kpayload_kbase_info;
};

struct kpayload_dump_info {
	uint16_t fw_version;
	uint64_t kaddr;
	uint64_t uaddr;
	size_t size;
};

struct kpayload_dump_args {
	void *syscall_handler;
	struct kpayload_dump_info *kpayload_dump_info;
};

struct kpayload_firmware_info {
  uint16_t fw_version;
};

struct kpayload_firmware_args {
  void *syscall_handler;
  struct kpayload_firmware_info *kpayload_firmware_info;
};

struct kpayload_kclock_info {
  uint16_t fw_version;
  uint64_t set_time;
};

struct kpayload_kclock_args {
  void *syscall_handler;
  struct kpayload_kclock_info *kpayload_kclock_info;
};

#define X86_CR0_WP (1 << 16)

static inline __attribute__((always_inline)) uint64_t __readmsr(unsigned long __register) {
  unsigned long __edx;
  unsigned long __eax;
  __asm__("rdmsr"
          : "=d"(__edx), "=a"(__eax)
          : "c"(__register));
  return (((uint64_t)__edx) << 32) | (uint64_t)__eax;
}

static inline __attribute__((always_inline)) uint64_t readCr0(void) {
  uint64_t cr0;
  __asm__ volatile("movq %0, %%cr0"
                   : "=r"(cr0)
                   :
                   : "memory");
  return cr0;
}

static inline __attribute__((always_inline)) void writeCr0(uint64_t cr0) {
  __asm__ volatile("movq %%cr0, %0"
                   :
                   : "r"(cr0)
                   : "memory");
}

#define copyout_macro(x) { \
  kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K ## x ## _XFAST_SYSCALL]; \
  copyout = (void *)(kernel_base + K ## x ## _COPYOUT); \
}

#define jailbreak_macro(x) { \
  kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K ## x ## _XFAST_SYSCALL]; \
  kernel_ptr = (uint8_t *)kernel_base; \
  got_prison0 = (void **)&kernel_ptr[K ## x ## _PRISON_0]; \
  got_rootvnode = (void **)&kernel_ptr[K ## x ## _ROOTVNODE]; \
}

#define mmap_macro(x) { \
  kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K ## x ## _XFAST_SYSCALL]; \
  kernel_ptr = (uint8_t *)kernel_base; \
  mmap_patch_1 = &kernel_ptr[K ## x ## _MMAP_SELF_1]; \
  mmap_patch_2 = &kernel_ptr[K ## x ## _MMAP_SELF_2]; \
  mmap_patch_3 = &kernel_ptr[K ## x ## _MMAP_SELF_3]; \
}

#define kclock_macro(x) { \
  kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K ## x ## _XFAST_SYSCALL]; \
  kernel_ptr = (uint8_t *)kernel_base; \
  if (x >= 450) { \
    *(void **)(&sceSblSrtcClearTimeDifference) = &kernel_ptr[K ## x ## _CLEAR_TIME_DIFFERENCE]; \
    sceSblSrtcClearTimeDifference(15); \
  } \
  *(void **)(&sceSblSrtcSetTime) = &kernel_ptr[K ## x ## _SET_TIME]; \
}

#define activate_browser_macro(x) { \
  kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K ## x ## _XFAST_SYSCALL]; \
  kernel_ptr = (uint8_t *)kernel_base; \
  *(void **)(&sceRegMgrSetInt) = &kernel_ptr[K ## x ## _REG_MGR_SET_INT]; \
}

int is_fw_spoofed();
int is_jailbroken();
int is_testkit();
int is_devkit();
int is_tid_spoofed();

uint16_t get_firmware();

uint64_t get_kernel_base();
int get_memory_dump(uint64_t kaddr, uint64_t *dump, size_t size);
int jailbreak();
int mmap_patch();
int kernel_clock(uint64_t value);
int activate_browser();

#endif
