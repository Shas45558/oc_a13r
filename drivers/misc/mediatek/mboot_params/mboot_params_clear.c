// SPDX-License-Identifier: GPL-2.0-only

#include <linux/init.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/slab.h>
#include <linux/platform_device.h>

#define REBOOT_REASON_SIG 0x43474244 /* DBRR */

struct mem_desc_t {
	unsigned int start;
	unsigned int size;
	unsigned int def_type;
	unsigned int offset;
};

struct mboot_params_buffer {
	uint32_t sig;
	uint32_t off_pl;
	uint32_t off_lpl;
	uint32_t sz_pl;
	uint32_t off_lk;
	uint32_t off_llk;
	uint32_t sz_lk;
	uint32_t padding[3];
	uint32_t sz_buffer;
	uint32_t off_linux;
	uint32_t filling[4];
};

static void __iomem *sram_base = NULL;

static int __init mboot_params_clear_init(void)
{
	struct mem_desc_t *sram;
	struct device_node *np;
	struct mboot_params_buffer *buf;
	int len, ret = 0;

	np = of_find_node_by_path("/chosen");
	if (!np)
		np = of_find_node_by_path("/chosen@0");

	if (!np) {
		pr_err("mboot_params_clear: Failed to find /chosen node");
		return -ENODEV;
	}

	sram = (struct mem_desc_t *)of_get_property(np,
						    "ram_console",
						    NULL);
	if (!sram) {
		ret = -ENODEV;
		goto put;
	}

	pr_info("mboot_params_clear: ram console from dt 0x%x@0x%x, 0x%x(0x%x)",
			sram->size, sram->start,
			sram->def_type, sram->offset);

	sram_base = ioremap_wc(sram->start, sram->size);
	if (!sram_base) {
		pr_err("mboot_params_clear: ioremap_wc failed for 0x%llx", sram->start);
		ret = -ENOMEM;
		goto put;
	}

	buf = (struct mboot_params_buffer *)sram_base;

	/* Clear previous reboot reason data */
	memset_io(sram_base, 0, sram->size);
	writel(0, &buf->off_pl);
	writel(0, &buf->sz_pl);
	writel(128, &buf->off_lk);
	writel(0, &buf->sz_lk);
	writel(512, &buf->off_linux);
	writel(REBOOT_REASON_SIG, &buf->sig);
	writel(sram->size, &buf->sz_buffer);

put:
	of_node_put(np);
	return ret;
}

static void __exit mboot_params_clear_exit(void)
{
	if (sram_base)
		iounmap(sram_base);
}

module_init(mboot_params_clear_init);
module_exit(mboot_params_clear_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("mboot-params-clear");
