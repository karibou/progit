/*
 * elf_info.h
 *
 * Copyright (C) 2011  NEC Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#ifndef _ELF_INFO_H
#define _ELF_INFO_H

#include <elf.h>
#include <sys/types.h>

#define ERASEINFO_NOTE_NAME		"ERASEINFO"
#define ERASEINFO_NOTE_NAME_BYTES	(sizeof(ERASEINFO_NOTE_NAME))

#define MAX_SIZE_NHDR	MAX(sizeof(Elf64_Nhdr), sizeof(Elf32_Nhdr))


off_t paddr_to_offset(unsigned long long paddr);
off_t paddr_to_offset2(unsigned long long paddr, off_t hint);
unsigned long long vaddr_to_paddr_general(unsigned long long vaddr);
off_t vaddr_to_offset_slow(int fd, char *filename, unsigned long long vaddr);
unsigned long long get_max_paddr(void);

int get_elf64_ehdr(int fd, char *filename, Elf64_Ehdr *ehdr);
int get_elf32_ehdr(int fd, char *filename, Elf32_Ehdr *ehdr);
int get_elf_info(int fd, char *filename);
void free_elf_info(void);

int is_elf64_memory(void);
int is_xen_memory(void);

int get_phnum_memory(void);
int get_phdr_memory(int index, Elf64_Phdr *phdr);
off_t get_offset_pt_load_memory(void);
int get_pt_load(int idx,
	unsigned long long *phys_start,
	unsigned long long *phys_end,
	unsigned long long *virt_start,
	unsigned long long *virt_end);
unsigned int get_num_pt_loads(void);

void set_nr_cpus(int num);
int get_nr_cpus(void);

int has_pt_note(void);
void set_pt_note(off_t offset, unsigned long size);
void get_pt_note(off_t *offset, unsigned long *size);

int has_vmcoreinfo(void);
void set_vmcoreinfo(off_t offset, unsigned long size);
void get_vmcoreinfo(off_t *offset, unsigned long *size);

int has_vmcoreinfo_xen(void);
void get_vmcoreinfo_xen(off_t *offset, unsigned long *size);
void get_xen_crash_info(off_t *offset, unsigned long *size);

int has_eraseinfo(void);
void get_eraseinfo(off_t *offset, unsigned long *size);
void set_eraseinfo(off_t offset, unsigned long size);

unsigned long get_xen_p2m_mfn(void);

#endif  /* ELF_INFO_H */


