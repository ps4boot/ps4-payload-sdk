#include "file.h"
#include "fw_defines.h"
#include "kernel.h"
#include "libc.h"

#include "payload_utils.h"

int is_fw_spoofed() {
  // TODO
  return 0;
}

int is_jailbroken() {
  // TODO
  return 0;
}

int is_testkit() {
  // TODO
  return 0;
}

int is_devkit() {
  // TODO
  return 0;
}

int is_tid_spoofed() {
  // TODO
  return 0;
}

int kpayload_base(struct thread *td, uint16_t fw_version, uint64_t *uaddr) {
  // TODO
  return 0;
}

int kpayload_dump(struct thread *td, uint16_t fw_version, uint64_t kaddr, uint64_t *uaddr, size_t size) {
  // TODO
  return 0;
}

int kpayload_jailbreak(struct thread *td, uint16_t fw_version) {
  struct filedesc *fd;
  struct ucred *cred;
  fd = td->td_proc->p_fd;
  cred = td->td_proc->p_ucred;

  void *kernel_base;
  uint8_t *kernel_ptr;
  void **got_prison0;
  void **got_rootvnode;

  if (fw_version == 350) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K350_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K350_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K350_ROOTVNODE];
  } else if (fw_version == 355) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K355_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K355_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K355_ROOTVNODE];
  } else if (fw_version == 370) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K370_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K370_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K370_ROOTVNODE];
  } else if (fw_version == 400) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K400_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K400_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K400_ROOTVNODE];
  } else if (fw_version == 401) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K401_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K401_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K401_ROOTVNODE];
  } else if (fw_version == 405) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K405_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K405_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K405_ROOTVNODE];
  } else if (fw_version == 406) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K406_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K406_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K406_ROOTVNODE];
  } else if (fw_version == 407) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K407_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K407_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K407_ROOTVNODE];
  } else if (fw_version == 450) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K450_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K450_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K450_ROOTVNODE];
  } else if (fw_version == 455) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K455_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K455_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K455_ROOTVNODE];
  } else if (fw_version == 470) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K470_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K470_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K470_ROOTVNODE];
  } else if (fw_version == 471) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K471_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K471_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K471_ROOTVNODE];
  } else if (fw_version == 472) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K472_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K472_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K472_ROOTVNODE];
  } else if (fw_version == 473) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K473_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K473_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K473_ROOTVNODE];
  } else if (fw_version == 474) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K474_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K474_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K474_ROOTVNODE];
  } else if (fw_version == 500) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K500_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K500_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K500_ROOTVNODE];
  } else if (fw_version == 501) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K501_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K501_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K501_ROOTVNODE];
  } else if (fw_version == 503) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K503_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K503_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K503_ROOTVNODE];
  } else if (fw_version == 505) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K505_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K505_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K505_ROOTVNODE];
  } else if (fw_version == 507) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K507_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K507_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K507_ROOTVNODE];
  } else if (fw_version == 550) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K550_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K550_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K550_ROOTVNODE];
  } else if (fw_version == 553) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K553_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K553_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K553_ROOTVNODE];
  } else if (fw_version == 555) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K555_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K555_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K555_ROOTVNODE];
  } else if (fw_version == 556) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K556_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K556_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K556_ROOTVNODE];
  } else if (fw_version == 600) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K600_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K600_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K600_ROOTVNODE];
  } else if (fw_version == 602) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K602_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K602_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K602_ROOTVNODE];
  } else if (fw_version == 620) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K620_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K620_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K620_ROOTVNODE];
  } else if (fw_version == 650) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K650_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K650_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K650_ROOTVNODE];
  } else if (fw_version == 651) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K651_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K651_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K651_ROOTVNODE];
  } else if (fw_version == 670) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K670_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K670_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K670_ROOTVNODE];
  } else if (fw_version == 671) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K671_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K671_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K671_ROOTVNODE];
  } else if (fw_version == 672) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K672_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K672_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K672_ROOTVNODE];
  } else if (fw_version == 700) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K700_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K700_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K700_ROOTVNODE];
  } else if (fw_version == 701) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K701_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K701_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K701_ROOTVNODE];
  } else if (fw_version == 702) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K702_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K702_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K702_ROOTVNODE];
  } else if (fw_version == 750) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K750_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K750_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K750_ROOTVNODE];
  } else if (fw_version == 751) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K751_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K751_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K751_ROOTVNODE];
  } else if (fw_version == 755) {
    kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K755_XFAST_SYSCALL];
    kernel_ptr = (uint8_t *)kernel_base;
    got_prison0 = (void **)&kernel_ptr[K755_PRISON_0];
    got_rootvnode = (void **)&kernel_ptr[K755_ROOTVNODE];
  } else {
    return -1;
  }

  cred->cr_uid = 0;
  cred->cr_ruid = 0;
  cred->cr_rgid = 0;
  cred->cr_groups[0] = 0;

  cred->cr_prison = *got_prison0;
  fd->fd_rdir = fd->fd_jdir = *got_rootvnode;

  void *td_ucred = *(void **)(((char *)td) + 304);

  uint64_t *sonyCred = (uint64_t *)(((char *)td_ucred) + 96);
  *sonyCred = 0xffffffffffffffff;

  uint64_t *sceProcessAuthorityId = (uint64_t *)(((char *)td_ucred) + 88);
  *sceProcessAuthorityId = 0x3801000000000013;

  uint64_t *sceProcCap = (uint64_t *)(((char *)td_ucred) + 104);
  *sceProcCap = 0xffffffffffffffff;

  return 0;
}

int kpayload_mmap(struct thread *td, uint16_t fw_version) {
  // TODO
  return 0;
}

int kpayload_kernel_clock(struct thread *td, uint16_t fw_version, uint32_t value) {
  // TODO
  return 0;
}

int kpayload_activate_browser(struct thread *td, uint16_t fw_version) {
  // TODO
  return 0;
}

uint16_t get_firmware() {
  uint16_t ret; // Numerical representation of the firmware version. ex: 505 for 5.05, 702 for 7.02, etc
  char binary_fw[2] = { 0 }; // 0x0000
  char string_fw[5] = { 0 }; // "0000\0"
  char sandbox_path[40]; // `/XXXXXXXXXX/system/common/lib/libc.sprx` [Char count of 39 + nullterm]

  snprintf(sandbox_path, sizeof(sandbox_path), "/%s/system/common/lib/libc.sprx", sceKernelGetFsSandboxRandomWord());

  int fd = sceKernelOpen(sandbox_path, O_RDONLY, 0);
  if (fd < 0) {
    // Assume it's currently jailbroken
    fd = sceKernelOpen("/system/common/lib/libc.sprx", O_RDONLY, 0);
  }

  if (fd >= 0) {
    sceKernelLseek(fd, 0x374, SEEK_CUR);
    sceKernelRead(fd, &binary_fw, 2);
    sceKernelClose(fd);

    snprintf(string_fw, sizeof(string_fw), "%02x%02x", binary_fw[1], binary_fw[0]);
  }
  ret = atoi(string_fw);

  return ret;
}

int get_kernel_base() {
  // uint16_t fw_version = get_firmware();
  // TODO
  return 0;
}

int get_kernel_chunk() {
  // uint16_t fw_version = get_firmware();
  // TODO
  return 0;
}

int jailbreak() {
  uint16_t fw_version = get_firmware();
  kexec(&kpayload_jailbreak, &fw_version);
  return 0;
}

int mmap_patch() {
  uint16_t fw_version = get_firmware();
  kexec(&kpayload_mmap, &fw_version);
  return 0;
}

int kernel_clock(uint32_t value) {
  // uint16_t fw_version = get_firmware();
  // TODO
  return 0;
}

int activate_browser() {
  uint16_t fw_version = get_firmware();
  kexec(&kpayload_activate_browser, &fw_version);
  return 0;
}
