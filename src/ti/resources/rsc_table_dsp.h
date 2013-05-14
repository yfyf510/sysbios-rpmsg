/*
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== rsc_table_dsp.h ========
 *
 *  Define the resource table entries for all DSP cores. This will be
 *  incorporated into corresponding base images, and used by the remoteproc
 *  on the host-side to allocated/reserve resources.
 *
 */

#ifndef _RSC_TABLE_DSP_H_
#define _RSC_TABLE_DSP_H_

#include <ti/resources/rsc_types.h>
#include <ti/gates/hwspinlock/HwSpinlock.h>

/* DSP Memory Map */
#define L4_44XX_BASE            0x4A000000

#define L4_PERIPHERAL_L4CFG     (L4_44XX_BASE)
#define DSP_PERIPHERAL_L4CFG    0x4A000000

#define L4_PERIPHERAL_L4PER     0x48000000
#define DSP_PERIPHERAL_L4PER    0x48000000

#define L4_PERIPHERAL_L4EMU     0x54000000
#define DSP_PERIPHERAL_L4EMU    0x54000000

#define L3_PERIPHERAL_DMM       0x4E000000
#define DSP_PERIPHERAL_DMM      0x4E000000

#define L3_TILER_MODE_0_1       0x60000000
#define DSP_TILER_MODE_0_1      0x60000000

#define L3_TILER_MODE_2         0x70000000
#define DSP_TILER_MODE_2        0x70000000

#define L3_TILER_MODE_3         0x78000000
#define DSP_TILER_MODE_3        0x78000000

#define DSP_MEM_TEXT            0x20000000
/* Co-locate alongside TILER region for easier flushing */
#define DSP_MEM_IOBUFS          0x80000000
#define DSP_MEM_DATA            0x90000000
#define DSP_MEM_HEAP            0x90100000

#define DSP_MEM_IPC_DATA        0x9F000000
#define DSP_MEM_IPC_VRING       0xA0000000
#define DSP_MEM_RPMSG_VRING0    0xA0000000
#define DSP_MEM_RPMSG_VRING1    0xA0004000
#define DSP_MEM_VRING_BUFS0     0xA0040000
#define DSP_MEM_VRING_BUFS1     0xA0080000

#define DSP_MEM_IPC_VRING_SIZE  SZ_1M
#define DSP_MEM_IPC_DATA_SIZE   SZ_1M
#define DSP_MEM_TEXT_SIZE       SZ_1M
#define DSP_MEM_DATA_SIZE       SZ_1M
#define DSP_MEM_HEAP_SIZE       (SZ_1M * 3)
#if defined(OMAP4_512) || defined(OMAP5_512)
#define DSP_MEM_IOBUFS_SIZE     (SZ_1M * 0)
#else
#define DSP_MEM_IOBUFS_SIZE     (SZ_1M * 90)
#endif

/*
 * Assign fixed RAM addresses to facilitate a fixed MMU table.
 */
/* This address is derived from current IPU & ION carveouts */
#ifdef OMAP5
#define PHYS_MEM_IPC_VRING      0x82000000
#else
#define PHYS_MEM_IPC_VRING      0x82000000
#endif

/* Need to be identical to that of Ducati */
#define PHYS_MEM_IOBUFS         0xBA300000

/*
 * Sizes of the virtqueues (expressed in number of buffers supported,
 * and must be power of 2)
 */
#define DSP_RPMSG_VQ0_SIZE      256
#define DSP_RPMSG_VQ1_SIZE      256

/* flip up bits whose indices represent features we support */
#define RPMSG_DSP_C0_FEATURES         1

struct resource_table {
    UInt32 version;
    UInt32 num;
    UInt32 reserved[2];
    UInt32 offset[15];  /* Should match 'num' in actual definition */

    /* rpmsg vdev entry */
    struct fw_rsc_vdev rpmsg_vdev;
    struct fw_rsc_vdev_vring rpmsg_vring0;
    struct fw_rsc_vdev_vring rpmsg_vring1;

    /* text carveout entry */
    struct fw_rsc_carveout text_cout;

    /* data carveout entry */
    struct fw_rsc_carveout data_cout;

    /* heap carveout entry */
    struct fw_rsc_carveout heap_cout;

    /* ipcdata carveout entry */
    struct fw_rsc_carveout ipcdata_cout;

    /* trace entry */
    struct fw_rsc_trace trace;

    /* devmem entry */
    struct fw_rsc_devmem devmem0;

    /* devmem entry */
    struct fw_rsc_devmem devmem1;

    /* devmem entry */
    struct fw_rsc_devmem devmem2;

    /* devmem entry */
    struct fw_rsc_devmem devmem3;

    /* devmem entry */
    struct fw_rsc_devmem devmem4;

    /* devmem entry */
    struct fw_rsc_devmem devmem5;

    /* devmem entry */
    struct fw_rsc_devmem devmem6;

    /* devmem entry */
    struct fw_rsc_devmem devmem7;

    /* hwspinlock custom entry */
    struct fw_rsc_custom hwspin;
};

#define TRACEBUFADDR (UInt32)&ti_trace_SysMin_Module_State_0_outbuf__A
#define HWSPINKLOCKSTATEADDR (UInt32)&ti_gates_HwSpinlock_sharedState
#define HWSPINKLOCKNUMADDR (UInt32)&ti_gates_HwSpinlock_numLocks

#pragma DATA_SECTION(ti_resources_ResourceTable, ".resource_table")
#pragma DATA_ALIGN(ti_resources_ResourceTable, 4096)

struct resource_table ti_resources_ResourceTable = {
    1,      /* we're the first version that implements this */
    15,     /* number of entries in the table */
    0, 0,   /* reserved, must be zero */
    /* offsets to entries */
    {
        offsetof(struct resource_table, rpmsg_vdev),
        offsetof(struct resource_table, text_cout),
        offsetof(struct resource_table, data_cout),
        offsetof(struct resource_table, heap_cout),
        offsetof(struct resource_table, ipcdata_cout),
        offsetof(struct resource_table, trace),
        offsetof(struct resource_table, devmem0),
        offsetof(struct resource_table, devmem1),
        offsetof(struct resource_table, devmem2),
        offsetof(struct resource_table, devmem3),
        offsetof(struct resource_table, devmem4),
        offsetof(struct resource_table, devmem5),
        offsetof(struct resource_table, devmem6),
        offsetof(struct resource_table, devmem7),
        offsetof(struct resource_table, hwspin),
    },

    /* rpmsg vdev entry */
    {
        TYPE_VDEV, VIRTIO_ID_RPMSG, 0,
        RPMSG_DSP_C0_FEATURES, 0, 0, 0, 2, { 0, 0 },
        /* no config data */
    },
    /* the two vrings */
    { DSP_MEM_RPMSG_VRING0, 4096, DSP_RPMSG_VQ0_SIZE, 1, 0 },
    { DSP_MEM_RPMSG_VRING1, 4096, DSP_RPMSG_VQ1_SIZE, 2, 0 },

    {
        TYPE_CARVEOUT,
        DSP_MEM_TEXT, 0,
        DSP_MEM_TEXT_SIZE, 0, 0, "DSP_MEM_TEXT",
    },

    {
        TYPE_CARVEOUT,
        DSP_MEM_DATA, 0,
        DSP_MEM_DATA_SIZE, 0, 0, "DSP_MEM_DATA",
    },

    {
        TYPE_CARVEOUT,
        DSP_MEM_HEAP, 0,
        DSP_MEM_HEAP_SIZE, 0, 0, "DSP_MEM_HEAP",
    },

    {
        TYPE_CARVEOUT,
        DSP_MEM_IPC_DATA, 0,
        DSP_MEM_IPC_DATA_SIZE, 0, 0, "DSP_MEM_IPC_DATA",
    },

    {
        TYPE_TRACE, TRACEBUFADDR, 0x8000, 0, "trace:dsp",
    },

    {
        TYPE_DEVMEM,
        DSP_MEM_IPC_VRING, PHYS_MEM_IPC_VRING,
        DSP_MEM_IPC_VRING_SIZE, 0, 0, "DSP_MEM_IPC_VRING",
    },

    {
        TYPE_DEVMEM,
        DSP_MEM_IOBUFS, PHYS_MEM_IOBUFS,
        DSP_MEM_IOBUFS_SIZE, 0, 0, "DSP_MEM_IOBUFS",
    },

    {
        TYPE_DEVMEM,
        DSP_TILER_MODE_0_1, L3_TILER_MODE_0_1,
        SZ_256M, 0, 0, "DSP_TILER_MODE_0_1",
    },

    {
        TYPE_DEVMEM,
        DSP_TILER_MODE_2, L3_TILER_MODE_2,
        SZ_128M, 0, 0, "DSP_TILER_MODE_2",
    },

    {
        TYPE_DEVMEM,
        DSP_TILER_MODE_3, L3_TILER_MODE_3,
        SZ_128M, 0, 0, "DSP_TILER_MODE_3",
    },

    {
        TYPE_DEVMEM,
        DSP_PERIPHERAL_L4CFG, L4_PERIPHERAL_L4CFG,
        SZ_16M, 0, 0, "DSP_PERIPHERAL_L4CFG",
    },

    {
        TYPE_DEVMEM,
        DSP_PERIPHERAL_L4PER, L4_PERIPHERAL_L4PER,
        SZ_16M, 0, 0, "DSP_PERIPHERAL_L4PER",
    },

    {
        TYPE_DEVMEM,
        DSP_PERIPHERAL_DMM, L3_PERIPHERAL_DMM,
        SZ_1M, 0, 0, "DSP_PERIPHERAL_DMM",
    },

    {
        TYPE_CUSTOM, TYPE_HWSPIN,
        sizeof(struct fw_rsc_custom_hwspin),
        { HWSPINKLOCKNUMADDR, HWSPINKLOCKSTATEADDR, "hwspin"},
    },
};

#endif /* _RSC_TABLE_DSP_H_ */
