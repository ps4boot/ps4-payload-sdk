#include "debug.h"
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

  char temp[0x1C];
  snprintf(temp, 0x1C, "%s", ssv_fw.version_string);

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
  int fd = open("/user/.jailbreak", O_WRONLY, 0777);
  if (fd >= 0) {
    close(fd);
    unlink("/user/.jailbreak");
    return 1;
  } else {
    return 0;
  }
}

int kpayload_kbase(struct thread *td, struct kpayload_kbase_args *args) {
  UNUSED(td);
  void *kernel_base;

  int (*copyout)(const void *kaddr, void *uaddr, size_t len);

  uint16_t fw_version = args->kpayload_kbase_info->fw_version;

  // NOTE: This is a C preprocessor macro
  build_kpayload(fw_version, copyout_macro);

  uint64_t uaddr = args->kpayload_kbase_info->uaddr;
  copyout(&kernel_base, (uint64_t *)uaddr, 8);

  return 0;
}

int kpayload_dump(struct thread *td, struct kpayload_dump_args *args) {
  UNUSED(td);
  void *kernel_base;

  int (*copyout)(const void *kaddr, void *uaddr, size_t len);

  uint16_t fw_version = args->kpayload_dump_info->fw_version;

  // NOTE: This is a C preprocessor macro
  build_kpayload(fw_version, copyout_macro);

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

  // NOTE: This is a C preprocessor macro
  build_kpayload(fw_version, jailbreak_macro);

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

  // NOTE: This is a C preprocessor macro
  build_kpayload(fw_version, mmap_macro);

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

int kpayload_aslr(struct thread *td, struct kpayload_firmware_args *args) {
  UNUSED(td);
  void *kernel_base;
  uint8_t *kernel_ptr;

  uint8_t *kmem;
  uint8_t *aslr_patch;

  uint16_t fw_version = args->kpayload_firmware_info->fw_version;

  // NOTE: This is a C preprocessor macro
  build_kpayload(fw_version, aslr_macro);

  uint64_t cr0 = readCr0();
  writeCr0(cr0 & ~X86_CR0_WP);

  // This may change depending on new firmware's function structure
  kmem = (uint8_t *)aslr_patch;
  if (fw_version < 600 || fw_version > 755) {
    kmem[0] = 0x90;
    kmem[1] = 0x90;
  } else {
    kmem[0] = 0xEB;
  }

  writeCr0(cr0);

  return 0;
}

int kpayload_kernel_clock(struct thread *td, struct kpayload_kclock_args *args) {
  UNUSED(td);
  void *kernel_base;

  void (*sceSblSrtcSetTime)(uint64_t tm);
  void (*sceSblSrtcClearTimeDifference)(uint64_t value);

  uint16_t fw_version = args->kpayload_kclock_info->fw_version;

  // NOTE: This is a C preprocessor macro
  build_kpayload(fw_version, kclock_macro);

  uint64_t set_time = args->kpayload_kclock_info->set_time;

  sceSblSrtcSetTime(set_time);

  return 0;
}

int kpayload_enable_browser(struct thread *td, struct kpayload_firmware_args *args) {
  UNUSED(td);
  void *kernel_base;

  uint64_t (*sceRegMgrSetInt)(uint32_t regId, int value);

  uint16_t fw_version = args->kpayload_firmware_info->fw_version;

  // NOTE: This is a C preprocessor macro
  build_kpayload(fw_version, enable_browser_macro);

  sceRegMgrSetInt(0x3C040000, 0);

  return 0;
}

int kpayload_target_id(struct thread *td, struct kpayload_target_id_args *args) {
  UNUSED(td);
  void *kernel_base;
  uint8_t *kernel_ptr;

  uint8_t *kmem;
  uint8_t *tid_patch;

  uint16_t fw_version = args->kpayload_target_id_info->fw_version;
  uint8_t spoof = args->kpayload_target_id_info->spoof;

  // NOTE: This is a C preprocessor macro
  build_kpayload(fw_version, tid_macro);

  uint64_t cr0 = readCr0();
  writeCr0(cr0 & ~X86_CR0_WP);

  kmem = (uint8_t *)tid_patch;
  kmem[0] = spoof;

  writeCr0(cr0);

  return 0;
}

int kpayload_perm_uart(struct thread *td, struct kpayload_firmware_args *args) {
  UNUSED(td);
  void *kernel_base;

  uint64_t (*icc_nvs_write)(uint32_t block, uint32_t offset, uint32_t size, void *value);

  uint16_t fw_version = args->kpayload_firmware_info->fw_version;

  // NOTE: This is a C preprocessor macro
  build_kpayload(fw_version, perm_uart_macro);

  char uart = 1;
  icc_nvs_write(4, 0x31F, 1, &uart);

  return 0;
}

uint16_t get_firmware() {
  if (g_firmware) {
    return g_firmware;
  }

  uint16_t ret;                   // Numerical representation of the firmware version. ex: 505 for 5.05, 702 for 7.02, etc
  uint32_t offset;                // Offset for firmware's version location
  uint16_t elf_header_size;       // ELF header size
  uint16_t elf_header_entry_size; // ELF header entry size
  uint16_t num_of_elf_entries;    // Number of entries in the ELF header
  char binary_fw[2] = {0};        // 0x0000
  char string_fw[5] = {0};        // "0000\0"
  char sandbox_path[33];          // `/XXXXXXXXXX/common/lib/libc.sprx` [Char count of 32 + nullterm]

  snprintf_s(sandbox_path, sizeof(sandbox_path), "/%s/common/lib/libc.sprx", sceKernelGetFsSandboxRandomWord());
  int fd = open(sandbox_path, O_RDONLY, 0);
  if (fd < 0) {
    // Assume it's currently jailbroken
    fd = open("/system/common/lib/libc.sprx", O_RDONLY, 0);
    if (fd < 0) {
      // It's really broken
      return -1;
    }
  }

  lseek(fd, 0x154, SEEK_SET);
  read(fd, &elf_header_size, sizeof(elf_header_size));
  read(fd, &elf_header_entry_size, sizeof(elf_header_entry_size));
  read(fd, &num_of_elf_entries, sizeof(num_of_elf_entries));
  offset = elf_header_size + num_of_elf_entries * elf_header_entry_size;

  // Align
  while (offset % 0x10 != 0) {
    offset += 1;
  }

  // 0x120 is the size of the header on encrypted ELFs, 0x14 is the location of the version after the ELF headers
  offset += 0x120 + 0x14;

  lseek(fd, offset, SEEK_SET);
  read(fd, &binary_fw, sizeof(binary_fw));
  close(fd);

  snprintf_s(string_fw, sizeof(string_fw), "%02x%02x", binary_fw[1], binary_fw[0]);

  ret = atoi(string_fw);

  g_firmware = ret;
  return ret;
}

int get_firmware_string(char *fw_string) {
  uint16_t fw_version = get_firmware();

  sprintf(fw_string, "%i", fw_version);

  if (fw_version < 10) {
    sprintf(fw_string, "0.0%c", fw_string[0]);
  } else if (fw_version < 100) {
    sprintf(fw_string, "0.%c%c", fw_string[0], fw_string[1]);
  } else if (fw_version < 1000) {
    sprintf(fw_string, "%c.%c%c", fw_string[0], fw_string[1], fw_string[2]);
  } else if (fw_version < 10000) {
    sprintf(fw_string, "%c%c.%c%c", fw_string[0], fw_string[1], fw_string[2], fw_string[3]);
  } else {
    return -1;
  }

  return 0;
}

uint64_t get_kernel_base() {
  uint64_t kernel_base;
  uint64_t *kernel_base_ptr = mmap(NULL, 8, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0); // Allocate a buffer in userland
  struct kpayload_kbase_info kpayload_kbase_info;
  kpayload_kbase_info.fw_version = get_firmware();
  kpayload_kbase_info.uaddr = (uint64_t)kernel_base_ptr;
  if (kexec(&kpayload_kbase, &kpayload_kbase_info) < 0) {
    kernel_base = -1;
  } else {
    memcpy(&kernel_base, kernel_base_ptr, 8);
  }
  munmap(kernel_base_ptr, 8);
  return kernel_base;
}

int get_memory_dump(uint64_t kaddr, uint64_t *uaddr, size_t size) {
  struct kpayload_dump_info kpayload_dump_info;
  kpayload_dump_info.fw_version = get_firmware();
  kpayload_dump_info.kaddr = kaddr;
  kpayload_dump_info.uaddr = (uint64_t)uaddr;
  kpayload_dump_info.size = size;
  return kexec(&kpayload_dump, &kpayload_dump_info);
}

int jailbreak() {
  if (is_jailbroken()) {
    return 0;
  }
  struct kpayload_firmware_info kpayload_firmware_info;
  kpayload_firmware_info.fw_version = get_firmware();
  return kexec(&kpayload_jailbreak, &kpayload_firmware_info);
}

int mmap_patch() {
  struct kpayload_firmware_info kpayload_firmware_info;
  kpayload_firmware_info.fw_version = get_firmware();
  return kexec(&kpayload_mmap, &kpayload_firmware_info);
}

int disable_aslr() {
  struct kpayload_firmware_info kpayload_firmware_info;
  kpayload_firmware_info.fw_version = get_firmware();
  return kexec(&kpayload_aslr, &kpayload_firmware_info);
}

int kernel_clock(uint64_t set_time) {
  struct kpayload_kclock_info kpayload_kclock_info;
  kpayload_kclock_info.fw_version = get_firmware();
  kpayload_kclock_info.set_time = set_time;
  return kexec(&kpayload_kernel_clock, &kpayload_kclock_info);
}

int enable_browser() {
  struct kpayload_firmware_info kpayload_firmware_info;
  kpayload_firmware_info.fw_version = get_firmware();
  return kexec(&kpayload_enable_browser, &kpayload_firmware_info);
}

int spoof_target_id(uint8_t id) {
  struct kpayload_target_id_info kpayload_target_id_info;
  kpayload_target_id_info.fw_version = get_firmware();
  kpayload_target_id_info.spoof = id;
  return kexec(&kpayload_target_id, &kpayload_target_id_info);
}

int enable_perm_uart() {
  struct kpayload_firmware_info kpayload_firmware_info;
  kpayload_firmware_info.fw_version = get_firmware();
  return kexec(&kpayload_perm_uart, &kpayload_firmware_info);
}
