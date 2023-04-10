/* SPDX-License-Identifier: GPL-2.0-only */

/*
 * ACPI - create the Fixed ACPI Description Tables (FADT)
 */

#include <console/console.h>
#include <acpi/acpi.h>
#include <acpi/acpigen.h>
#include <device/pci_ops.h>
#include <arch/ioapic.h>
#include <arch/smp/mpspec.h>
#include <cpu/amd/cpuid.h>
#include <cpu/x86/smm.h>
#include <device/device.h>
#include <device/pci.h>
#include <gpio.h>
#include <amdblocks/acpimmio.h>
#include <amdblocks/acpi.h>
#include <amdblocks/chip.h>
#include <amdblocks/cpu.h>
#include <amdblocks/ioapic.h>
#include <soc/acpi.h>
#include <soc/pci_devs.h>
#include <soc/southbridge.h>
#include "chip.h"

unsigned long acpi_fill_madt(unsigned long current)
{
	current += acpi_create_madt_ioapic_from_hw((acpi_madt_ioapic_t *)current, IO_APIC_ADDR);

	current += acpi_create_madt_ioapic_from_hw((acpi_madt_ioapic_t *)current,
						   GNB_IO_APIC_ADDR);

	/* PIT is connected to legacy IRQ 0, but IOAPIC GSI 2 */
	current += acpi_create_madt_irqoverride((acpi_madt_irqoverride_t *)current,
			MP_BUS_ISA, 0, 2,
			MP_IRQ_TRIGGER_DEFAULT | MP_IRQ_POLARITY_DEFAULT);
	/* SCI IRQ type override */
	current += acpi_create_madt_irqoverride((acpi_madt_irqoverride_t *)current,
			MP_BUS_ISA, ACPI_SCI_IRQ, ACPI_SCI_IRQ,
			MP_IRQ_TRIGGER_LEVEL | MP_IRQ_POLARITY_LOW);

	current = acpi_fill_madt_irqoverride(current);

	return current;
}

/*
 * Reference section 5.2.9 Fixed ACPI Description Table (FADT)
 * in the ACPI 3.0b specification.
 */
void acpi_fill_fadt(acpi_fadt_t *fadt)
{
	const struct soc_amd_common_config *cfg = soc_get_common_config();

	printk(BIOS_DEBUG, "pm_base: 0x%04x\n", ACPI_IO_BASE);

	if (permanent_smi_handler()) {
		fadt->smi_cmd = APM_CNT;
		fadt->acpi_enable = APM_CNT_ACPI_ENABLE;
		fadt->acpi_disable = APM_CNT_ACPI_DISABLE;
	}

	fadt->pm1a_evt_blk = ACPI_PM_EVT_BLK;
	fadt->pm1a_cnt_blk = ACPI_PM1_CNT_BLK;
	fadt->pm_tmr_blk = ACPI_PM_TMR_BLK;
	fadt->gpe0_blk = ACPI_GPE0_BLK;

	fadt->pm1_evt_len = 4;	/* 32 bits */
	fadt->pm1_cnt_len = 2;	/* 16 bits */
	fadt->pm_tmr_len = 4;	/* 32 bits */
	fadt->gpe0_blk_len = 8;	/* 64 bits */

	fill_fadt_extended_pm_regs(fadt);

	fadt->day_alrm = RTC_DATE_ALARM;
	fadt->iapc_boot_arch = cfg->fadt_boot_arch; /* legacy free default */
	fadt->flags |=	ACPI_FADT_WBINVD | /* See table 5-34 ACPI 6.3 spec */
			ACPI_FADT_C1_SUPPORTED |
			ACPI_FADT_S4_RTC_WAKE |
			ACPI_FADT_32BIT_TIMER |
			ACPI_FADT_PCI_EXPRESS_WAKE |
			ACPI_FADT_PLATFORM_CLOCK |
			ACPI_FADT_S4_RTC_VALID |
			ACPI_FADT_REMOTE_POWER_ON;
	fadt->flags |= cfg->fadt_flags; /* additional board-specific flags */
}

const acpi_cstate_t cstate_cfg_table[] = {
	[0] = {
		.ctype = 1,
		.latency = 1,
		.power = 0,
	},
	[1] = {
		.ctype = 2,
		.latency = 400,
		.power = 0,
	},
};

const acpi_cstate_t *get_cstate_config_data(size_t *size)
{
	*size = ARRAY_SIZE(cstate_cfg_table);
	return cstate_cfg_table;
}
