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
  if (getuid() == 0) {
    return 1;
  }
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

int kpayload_jailbreak(struct thread *td, struct kpayload_firmware_args *args) {
  struct filedesc *fd;
  struct ucred *cred;
  fd = td->td_proc->p_fd;
  cred = td->td_proc->p_ucred;

  void *kernel_base;
  uint8_t *kernel_ptr;
  void **got_prison0;
  void **got_rootvnode;

  uint16_t fw_version = args->kpayload_firmware_info->fw_version;

  // NOTE: `jailbreak_macro()` is a C preprocessor macro so it cannot have a
  //       variable as input, it is executed at compile time
  switch(fw_version) {
    case 350:
      jailbreak_macro(350);
    case 355:
      jailbreak_macro(355);
    case 370:
      jailbreak_macro(370);
    case 400:
      jailbreak_macro(400);
    case 401:
      jailbreak_macro(401);
    case 405:
      jailbreak_macro(405);
    case 406:
      jailbreak_macro(406);
    case 407:
      jailbreak_macro(407);
    case 450:
      jailbreak_macro(450);
    case 455:
      jailbreak_macro(455);
    case 470:
      jailbreak_macro(470);
    case 471:
      jailbreak_macro(471);
    case 472:
      jailbreak_macro(472);
    case 473:
      jailbreak_macro(473);
    case 474:
      jailbreak_macro(474);
    case 500:
      jailbreak_macro(500);
    case 501:
      jailbreak_macro(501);
    case 503:
      jailbreak_macro(503);
    case 505:
      jailbreak_macro(505);
    case 507:
      jailbreak_macro(507);
    case 550:
      jailbreak_macro(550);
    case 553:
      jailbreak_macro(553);
    case 555:
      jailbreak_macro(555);
    case 556:
      jailbreak_macro(556);
    case 600:
      jailbreak_macro(600);
    case 602:
      jailbreak_macro(602);
    case 620:
      jailbreak_macro(620);
    case 650:
      jailbreak_macro(650);
    case 651:
      jailbreak_macro(651);
    case 670:
      jailbreak_macro(670);
    case 671:
      jailbreak_macro(671);
    case 672:
      jailbreak_macro(672);
    case 700:
      jailbreak_macro(700);
    case 701:
      jailbreak_macro(701);
    case 702:
      jailbreak_macro(702);
    case 750:
      jailbreak_macro(750);
    case 751:
      jailbreak_macro(751);
    case 755:
      jailbreak_macro(755);
    default:
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

int kpayload_mmap(struct thread *td, struct kpayload_firmware_args *args) {
  void *kernel_base;
  uint8_t *kernel_ptr;

  uint8_t *kmem;

  uint8_t *mmap_patch_1;
  uint8_t *mmap_patch_2;
  uint8_t *mmap_patch_3;

  uint16_t fw_version = args->kpayload_firmware_info->fw_version;

  // NOTE: `mmap_macro()` is a C preprocessor macro so it cannot have a
  //       variable as input, it is executed at compile time
  switch(fw_version) {
    case 350:
      mmap_macro(350);
    case 355:
      mmap_macro(355);
    case 370:
      mmap_macro(370);
    case 400:
      mmap_macro(400);
    case 401:
      mmap_macro(401);
    case 405:
      mmap_macro(405);
    case 406:
      mmap_macro(406);
    case 407:
      mmap_macro(407);
    case 450:
      mmap_macro(450);
    case 455:
      mmap_macro(455);
    case 470:
      mmap_macro(470);
    case 471:
      mmap_macro(471);
    case 472:
      mmap_macro(472);
    case 473:
      mmap_macro(473);
    case 474:
      mmap_macro(474);
    case 500:
      mmap_macro(500);
    case 501:
      mmap_macro(501);
    case 503:
      mmap_macro(503);
    case 505:
      mmap_macro(505);
    case 507:
      mmap_macro(507);
    case 550:
      mmap_macro(550);
    case 553:
      mmap_macro(553);
    case 555:
      mmap_macro(555);
    case 556:
      mmap_macro(556);
    case 600:
      mmap_macro(600);
    case 602:
      mmap_macro(602);
    case 620:
      mmap_macro(620);
    case 650:
      mmap_macro(650);
    case 651:
      mmap_macro(651);
    case 670:
      mmap_macro(670);
    case 671:
      mmap_macro(671);
    case 672:
      mmap_macro(672);
    case 700:
      mmap_macro(700);
    case 701:
      mmap_macro(701);
    case 702:
      mmap_macro(702);
    case 750:
      mmap_macro(750);
    case 751:
      mmap_macro(751);
    case 755:
      mmap_macro(755);
    default:
      return -1;
  }

  uint64_t cr0 = readCr0();
  writeCr0(cr0 & ~X86_CR0_WP);

  kmem = (uint8_t *)mmap_patch_1;
  kmem[0] = 0xB8;
  kmem[1] = 0x01;
  kmem[2] = 0x00;
  kmem[3] = 0x00;
  kmem[4] = 0x00;
  kmem[5] = 0xC3;

  kmem = (uint8_t *)mmap_patch_2;
  kmem[0] = 0xB8;
  kmem[1] = 0x01;
  kmem[2] = 0x00;
  kmem[3] = 0x00;
  kmem[4] = 0x00;
  kmem[5] = 0xC3;

  kmem = (uint8_t *)mmap_patch_3;
  kmem[0] = 0x31;
  kmem[1] = 0xC0;
  kmem[2] = 0x90;
  kmem[3] = 0x90;
  kmem[4] = 0x90;

  writeCr0(cr0);

  return 0;
}

int kpayload_kernel_clock(struct thread *td, uint16_t fw_version, uint32_t value) {
  // TODO
  return 0;
}

int kpayload_activate_browser(struct thread *td,  struct kpayload_firmware_args *args) {
  void *kernel_base;
  uint8_t *kernel_ptr;

  uint64_t (*sceRegMgrSetInt)(uint32_t regId, int value);

  uint16_t fw_version = args->kpayload_firmware_info->fw_version;

  // NOTE: `activate_browser_macro()` is a C preprocessor macro so it cannot
  //       have a variable as input, it is executed at compile time
  switch(fw_version) {
    case 350:
      activate_browser_macro(350);
    case 355:
      activate_browser_macro(355);
    case 370:
      activate_browser_macro(370);
    case 400:
      activate_browser_macro(400);
    case 401:
      activate_browser_macro(401);
    case 405:
      activate_browser_macro(405);
    case 406:
      activate_browser_macro(406);
    case 407:
      activate_browser_macro(407);
    case 450:
      activate_browser_macro(450);
    case 455:
      activate_browser_macro(455);
    case 470:
      activate_browser_macro(470);
    case 471:
      activate_browser_macro(471);
    case 472:
      activate_browser_macro(472);
    case 473:
      activate_browser_macro(473);
    case 474:
      activate_browser_macro(474);
    case 500:
      activate_browser_macro(500);
    case 501:
      activate_browser_macro(501);
    case 503:
      activate_browser_macro(503);
    case 505:
      activate_browser_macro(505);
    case 507:
      activate_browser_macro(507);
    case 550:
      activate_browser_macro(550);
    case 553:
      activate_browser_macro(553);
    case 555:
      activate_browser_macro(555);
    case 556:
      activate_browser_macro(556);
    case 600:
      activate_browser_macro(600);
    case 602:
      activate_browser_macro(602);
    case 620:
      activate_browser_macro(620);
    case 650:
      activate_browser_macro(650);
    case 651:
      activate_browser_macro(651);
    case 670:
      activate_browser_macro(670);
    case 671:
      activate_browser_macro(671);
    case 672:
      activate_browser_macro(672);
    case 700:
      activate_browser_macro(700);
    case 701:
      activate_browser_macro(701);
    case 702:
      activate_browser_macro(702);
    case 750:
      activate_browser_macro(750);
    case 751:
      activate_browser_macro(751);
    case 755:
      activate_browser_macro(755);
    default:
      return -1;
  }

  sceRegMgrSetInt(0x3C040000, 0);

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
  // TODO
  return 0;
}

int get_kernel_chunk() {
  // TODO
  return 0;
}

int jailbreak() {
  if (is_jailbroken()) {
    return 0;
  }
  struct kpayload_firmware_info kpayload_firmware_info;
  kpayload_firmware_info.fw_version = get_firmware();
  kexec(&kpayload_jailbreak, &kpayload_firmware_info);
  return 0;
}

int mmap_patch() {
  struct kpayload_firmware_info kpayload_firmware_info;
  kpayload_firmware_info.fw_version = get_firmware();
  kexec(&kpayload_mmap, &kpayload_firmware_info);
  return 0;
}

int kernel_clock(uint32_t value) {
  // TODO
  return 0;
}

int activate_browser() {
  struct kpayload_firmware_info kpayload_firmware_info;
  kpayload_firmware_info.fw_version = get_firmware();
  kexec(&kpayload_activate_browser, &kpayload_firmware_info);
  return 0;
}
