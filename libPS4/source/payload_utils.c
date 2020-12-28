#include "file.h"
#include "fw_defines.h"
#include "kernel.h"
#include "libc.h"
#include "memory.h"

#include "payload_utils.h"

uint16_t g_firmware;

int is_fw_spoofed() {
  SceFwInfo ssv_fw;
  char ssv_fw_trimmed[5];
  uint16_t ssv_fw_final;

  uint16_t libc_fw = get_firmware();
  sceKernelGetSystemSwVersion(&ssv_fw);

  char temp[0x1c];
  snprintf(temp, 0x1c, "%s", ssv_fw.version_string);

  char *first = strtok(temp, ".");
  char *second = strtok(NULL, ".");

  sprintf(ssv_fw_trimmed, "%s%c%c", first, second[0], second[1]);

  ssv_fw_final = atoi(ssv_fw_trimmed);

  if (ssv_fw_final != libc_fw) {
    return 1;
  }

  return 0;
}

int is_jailbroken() {
  if (getuid() == 0) {
    return 0;
  }
  return 1;
}

int kpayload_kbase(struct thread *td, struct kpayload_kbase_args *args) {
  UNUSED(td);
  void *kernel_base;

  int (*copyout)(const void *kaddr, void *uaddr, size_t len) = 0;

  uint16_t fw_version = args->kpayload_kbase_info->fw_version;

  // NOTE: These are C preprocessor macros
  switch(fw_version) {
    caseentry(350, copyout_macro);
    caseentry(355, copyout_macro);
    caseentry(370, copyout_macro);
    caseentry(400, copyout_macro);
    caseentry(401, copyout_macro);
    caseentry(405, copyout_macro);
    caseentry(406, copyout_macro);
    caseentry(407, copyout_macro);
    caseentry(450, copyout_macro);
    caseentry(455, copyout_macro);
    caseentry(470, copyout_macro);
    caseentry(471, copyout_macro);
    caseentry(472, copyout_macro);
    caseentry(473, copyout_macro);
    caseentry(474, copyout_macro);
    caseentry(500, copyout_macro);
    caseentry(501, copyout_macro);
    caseentry(503, copyout_macro);
    caseentry(505, copyout_macro);
    caseentry(507, copyout_macro);
    caseentry(550, copyout_macro);
    caseentry(553, copyout_macro);
    caseentry(555, copyout_macro);
    caseentry(556, copyout_macro);
    caseentry(600, copyout_macro);
    caseentry(602, copyout_macro);
    caseentry(620, copyout_macro);
    caseentry(650, copyout_macro);
    caseentry(651, copyout_macro);
    caseentry(670, copyout_macro);
    caseentry(671, copyout_macro);
    caseentry(672, copyout_macro);
    caseentry(700, copyout_macro);
    caseentry(701, copyout_macro);
    caseentry(702, copyout_macro);
    caseentry(750, copyout_macro);
    caseentry(751, copyout_macro);
    caseentry(755, copyout_macro);
    default:
      return -1;
  }

  uint64_t uaddr = args->kpayload_kbase_info->uaddr;
  copyout(&kernel_base, (uint64_t *)uaddr, 8);

  return 0;
}

int kpayload_dump(struct thread *td, struct kpayload_dump_args* args) {
  UNUSED(td);
  void *kernel_base;

  int (*copyout)(const void *kaddr, void *uaddr, size_t len) = 0;

  uint16_t fw_version = args->kpayload_dump_info->fw_version;

  // NOTE: These are C preprocessor macros
  switch(fw_version) {
    caseentry(350, copyout_macro);
    caseentry(355, copyout_macro);
    caseentry(370, copyout_macro);
    caseentry(400, copyout_macro);
    caseentry(401, copyout_macro);
    caseentry(405, copyout_macro);
    caseentry(406, copyout_macro);
    caseentry(407, copyout_macro);
    caseentry(450, copyout_macro);
    caseentry(455, copyout_macro);
    caseentry(470, copyout_macro);
    caseentry(471, copyout_macro);
    caseentry(472, copyout_macro);
    caseentry(473, copyout_macro);
    caseentry(474, copyout_macro);
    caseentry(500, copyout_macro);
    caseentry(501, copyout_macro);
    caseentry(503, copyout_macro);
    caseentry(505, copyout_macro);
    caseentry(507, copyout_macro);
    caseentry(550, copyout_macro);
    caseentry(553, copyout_macro);
    caseentry(555, copyout_macro);
    caseentry(556, copyout_macro);
    caseentry(600, copyout_macro);
    caseentry(602, copyout_macro);
    caseentry(620, copyout_macro);
    caseentry(650, copyout_macro);
    caseentry(651, copyout_macro);
    caseentry(670, copyout_macro);
    caseentry(671, copyout_macro);
    caseentry(672, copyout_macro);
    caseentry(700, copyout_macro);
    caseentry(701, copyout_macro);
    caseentry(702, copyout_macro);
    caseentry(750, copyout_macro);
    caseentry(751, copyout_macro);
    caseentry(755, copyout_macro);
    default:
      return -1;
  }

  uint64_t kaddr = args->kpayload_dump_info->kaddr;
  uint64_t uaddr = args->kpayload_dump_info->uaddr;
  size_t size = args->kpayload_dump_info->size;

  int ret = copyout((uint64_t *)kaddr, (uint64_t *)uaddr, size);

  if (ret == -1) {
    memset((uint64_t *)uaddr, 0, size);
  }

  return ret;
}

int kpayload_jailbreak(struct thread *td, struct kpayload_firmware_args *args) {
  struct filedesc *fd;
  struct ucred *cred;
  fd = td->td_proc->p_fd;
  cred = td->td_proc->p_ucred;

  void *kernel_base;
  uint8_t *kernel_ptr;
  void **prison0;
  void **rootvnode;

  uint16_t fw_version = args->kpayload_firmware_info->fw_version;

  // NOTE: These are C preprocessor macros
  switch(fw_version) {
    caseentry(350, jailbreak_macro);
    caseentry(355, jailbreak_macro);
    caseentry(370, jailbreak_macro);
    caseentry(400, jailbreak_macro);
    caseentry(401, jailbreak_macro);
    caseentry(405, jailbreak_macro);
    caseentry(406, jailbreak_macro);
    caseentry(407, jailbreak_macro);
    caseentry(450, jailbreak_macro);
    caseentry(455, jailbreak_macro);
    caseentry(470, jailbreak_macro);
    caseentry(471, jailbreak_macro);
    caseentry(472, jailbreak_macro);
    caseentry(473, jailbreak_macro);
    caseentry(474, jailbreak_macro);
    caseentry(500, jailbreak_macro);
    caseentry(501, jailbreak_macro);
    caseentry(503, jailbreak_macro);
    caseentry(505, jailbreak_macro);
    caseentry(507, jailbreak_macro);
    caseentry(550, jailbreak_macro);
    caseentry(553, jailbreak_macro);
    caseentry(555, jailbreak_macro);
    caseentry(556, jailbreak_macro);
    caseentry(600, jailbreak_macro);
    caseentry(602, jailbreak_macro);
    caseentry(620, jailbreak_macro);
    caseentry(650, jailbreak_macro);
    caseentry(651, jailbreak_macro);
    caseentry(670, jailbreak_macro);
    caseentry(671, jailbreak_macro);
    caseentry(672, jailbreak_macro);
    caseentry(700, jailbreak_macro);
    caseentry(701, jailbreak_macro);
    caseentry(702, jailbreak_macro);
    caseentry(750, jailbreak_macro);
    caseentry(751, jailbreak_macro);
    caseentry(755, jailbreak_macro);
    default:
      return -1;
  }

  cred->cr_uid = 0;
  cred->cr_ruid = 0;
  cred->cr_rgid = 0;
  cred->cr_groups[0] = 0;

  cred->cr_prison = *prison0;
  fd->fd_rdir = fd->fd_jdir = *rootvnode;

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
  UNUSED(td);
  void *kernel_base;
  uint8_t *kernel_ptr;

  uint8_t *kmem;

  uint8_t *mmap_patch_1;
  uint8_t *mmap_patch_2;
  uint8_t *mmap_patch_3;

  uint16_t fw_version = args->kpayload_firmware_info->fw_version;

  // NOTE: These are C preprocessor macros
  switch(fw_version) {
    caseentry(350, mmap_macro);
    caseentry(355, mmap_macro);
    caseentry(370, mmap_macro);
    caseentry(400, mmap_macro);
    caseentry(401, mmap_macro);
    caseentry(405, mmap_macro);
    caseentry(406, mmap_macro);
    caseentry(407, mmap_macro);
    caseentry(450, mmap_macro);
    caseentry(455, mmap_macro);
    caseentry(470, mmap_macro);
    caseentry(471, mmap_macro);
    caseentry(472, mmap_macro);
    caseentry(473, mmap_macro);
    caseentry(474, mmap_macro);
    caseentry(500, mmap_macro);
    caseentry(501, mmap_macro);
    caseentry(503, mmap_macro);
    caseentry(505, mmap_macro);
    caseentry(507, mmap_macro);
    caseentry(550, mmap_macro);
    caseentry(553, mmap_macro);
    caseentry(555, mmap_macro);
    caseentry(556, mmap_macro);
    caseentry(600, mmap_macro);
    caseentry(602, mmap_macro);
    caseentry(620, mmap_macro);
    caseentry(650, mmap_macro);
    caseentry(651, mmap_macro);
    caseentry(670, mmap_macro);
    caseentry(671, mmap_macro);
    caseentry(672, mmap_macro);
    caseentry(700, mmap_macro);
    caseentry(701, mmap_macro);
    caseentry(702, mmap_macro);
    caseentry(750, mmap_macro);
    caseentry(751, mmap_macro);
    caseentry(755, mmap_macro);
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

int kpayload_kernel_clock(struct thread *td, struct kpayload_kclock_args *args) {
  UNUSED(td);
  void *kernel_base;

  void (*sceSblSrtcClearTimeDifference)(uint64_t value) = 0;
  void (*sceSblSrtcSetTime)(uint64_t tm) = 0;

  uint16_t fw_version = args->kpayload_kclock_info->fw_version;

  // NOTE: These are C preprocessor macros
  switch(fw_version) {
    caseentry(350, kclock_macro);
    caseentry(355, kclock_macro);
    caseentry(370, kclock_macro);
    caseentry(400, kclock_macro);
    caseentry(401, kclock_macro);
    caseentry(405, kclock_macro);
    caseentry(406, kclock_macro);
    caseentry(407, kclock_macro);
    caseentry(450, kclock_macro);
    caseentry(455, kclock_macro);
    caseentry(470, kclock_macro);
    caseentry(471, kclock_macro);
    caseentry(472, kclock_macro);
    caseentry(473, kclock_macro);
    caseentry(474, kclock_macro);
    caseentry(500, kclock_macro);
    caseentry(501, kclock_macro);
    caseentry(503, kclock_macro);
    caseentry(505, kclock_macro);
    caseentry(507, kclock_macro);
    caseentry(550, kclock_macro);
    caseentry(553, kclock_macro);
    caseentry(555, kclock_macro);
    caseentry(556, kclock_macro);
    caseentry(600, kclock_macro);
    caseentry(602, kclock_macro);
    caseentry(620, kclock_macro);
    caseentry(650, kclock_macro);
    caseentry(651, kclock_macro);
    caseentry(670, kclock_macro);
    caseentry(671, kclock_macro);
    caseentry(672, kclock_macro);
    caseentry(700, kclock_macro);
    caseentry(701, kclock_macro);
    caseentry(702, kclock_macro);
    caseentry(750, kclock_macro);
    caseentry(751, kclock_macro);
    caseentry(755, kclock_macro);
    default:
      return -1;
  }

  uint64_t set_time = args->kpayload_kclock_info->set_time;

  sceSblSrtcSetTime(set_time);

  return 0;
}

int kpayload_enable_browser(struct thread *td,  struct kpayload_firmware_args *args) {
  UNUSED(td);
  void *kernel_base;

  uint64_t (*sceRegMgrSetInt)(uint32_t regId, int value) = 0;

  uint16_t fw_version = args->kpayload_firmware_info->fw_version;

  // NOTE: These are C preprocessor macros
  switch(fw_version) {
    caseentry(350, enable_browser_macro);
    caseentry(355, enable_browser_macro);
    caseentry(370, enable_browser_macro);
    caseentry(400, enable_browser_macro);
    caseentry(401, enable_browser_macro);
    caseentry(405, enable_browser_macro);
    caseentry(406, enable_browser_macro);
    caseentry(407, enable_browser_macro);
    caseentry(450, enable_browser_macro);
    caseentry(455, enable_browser_macro);
    caseentry(470, enable_browser_macro);
    caseentry(471, enable_browser_macro);
    caseentry(472, enable_browser_macro);
    caseentry(473, enable_browser_macro);
    caseentry(474, enable_browser_macro);
    caseentry(500, enable_browser_macro);
    caseentry(501, enable_browser_macro);
    caseentry(503, enable_browser_macro);
    caseentry(505, enable_browser_macro);
    caseentry(507, enable_browser_macro);
    caseentry(550, enable_browser_macro);
    caseentry(553, enable_browser_macro);
    caseentry(555, enable_browser_macro);
    caseentry(556, enable_browser_macro);
    caseentry(600, enable_browser_macro);
    caseentry(602, enable_browser_macro);
    caseentry(620, enable_browser_macro);
    caseentry(650, enable_browser_macro);
    caseentry(651, enable_browser_macro);
    caseentry(670, enable_browser_macro);
    caseentry(671, enable_browser_macro);
    caseentry(672, enable_browser_macro);
    caseentry(700, enable_browser_macro);
    caseentry(701, enable_browser_macro);
    caseentry(702, enable_browser_macro);
    caseentry(750, enable_browser_macro);
    caseentry(751, enable_browser_macro);
    caseentry(755, enable_browser_macro);
    default:
      return -1;
  }

  sceRegMgrSetInt(0x3C040000, 0);

  return 0;
}

uint16_t get_firmware() {
  if (g_firmware) {
    return g_firmware;
  }
  uint16_t ret; // Numerical representation of the firmware version. ex: 505 for 5.05, 702 for 7.02, etc
  char binary_fw[2] = { 0 }; // 0x0000
  char string_fw[5] = { 0 }; // "0000\0"
  char sandbox_path[33]; // `/XXXXXXXXXX/common/lib/libc.sprx` [Char count of 32 + nullterm]

  snprintf(sandbox_path, sizeof(sandbox_path), "/%s/common/lib/libc.sprx", sceKernelGetFsSandboxRandomWord());

  FILE *fp = fopen(sandbox_path, "rb");
  if (!fp) {
    // Assume it's currently jailbroken
    fp = fopen("/system/common/lib/libc.sprx", "rb");
  }

  if (fp) {
    fseek(fp, 0x374, SEEK_CUR);
    fread(&binary_fw, sizeof(char), 2, fp);
    fclose(fp);

    snprintf(string_fw, sizeof(string_fw), "%02x%02x", binary_fw[1], binary_fw[0]);
  }
  ret = atoi(string_fw);

  g_firmware = ret;
  return ret;
}

uint64_t get_kernel_base() {
  uint64_t kernel_base;
  uint64_t *kernel_base_ptr = mmap(NULL, 8, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0); // Allocate a buffer in userland
  struct kpayload_kbase_info kpayload_kbase_info;
  kpayload_kbase_info.fw_version = get_firmware();
  kpayload_kbase_info.uaddr = (uint64_t)kernel_base_ptr;
  kexec(&kpayload_kbase, &kpayload_kbase_info);
  memcpy(&kernel_base, kernel_base_ptr, 8);
  munmap(kernel_base_ptr, 8);
  return kernel_base;
}

int get_memory_dump(uint64_t kaddr, uint64_t *uaddr, size_t size) {
  struct kpayload_dump_info kpayload_dump_info;
  kpayload_dump_info.fw_version = get_firmware();
  kpayload_dump_info.kaddr = kaddr;
  kpayload_dump_info.uaddr = (uint64_t)uaddr;
  kpayload_dump_info.size = size;
  kexec(&kpayload_dump, &kpayload_dump_info);
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

int kernel_clock(uint64_t set_time) {
  struct kpayload_kclock_info kpayload_kclock_info;
  kpayload_kclock_info.fw_version = get_firmware();
  kpayload_kclock_info.set_time = set_time;
  kexec(&kpayload_kernel_clock, &kpayload_kclock_info);
  return 0;
}

int enable_browser() {
  struct kpayload_firmware_info kpayload_firmware_info;
  kpayload_firmware_info.fw_version = get_firmware();
  kexec(&kpayload_enable_browser, &kpayload_firmware_info);
  return 0;
}
