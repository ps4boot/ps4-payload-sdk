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

/*
uint16_t get_firmware();
int get_kernel_base();
int get_kernel_chunk();

int is_fw_spoofed();
int is_jailbroken();
int is_testkit();
int is_devkit();
int is_tid_spoofed();

int kpayload_base(struct thread *td, uint16_t *fw_version, uint64_t *uaddr);
int kpayload_dump(struct thread *td, uint16_t *fw_version, uint64_t kaddr, uint64_t *uaddr, size_t size);
int kpayload_jailbreak(struct thread *td, uint16_t *fw_version);
int kpayload_mmap(struct thread *td, uint16_t *fw_version);
int kpayload_kernel_clock(struct thread *td, uint16_t *fw_version, uint32_t value);
int kpayload_activate_browser(struct thread *td, uint16_t *fw_version);
*/

#endif
