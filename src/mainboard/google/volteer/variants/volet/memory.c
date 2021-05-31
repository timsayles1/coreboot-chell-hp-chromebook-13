/* SPDX-License-Identifier: GPL-2.0-only */

#include <baseboard/variants.h>

static const struct mb_cfg board_memcfg = {
	.type = MEM_TYPE_LP4X,

	/* DQ byte map */
	.lp4x_dq_map = {
		.ddr0 = {
			.dq0 = { 3,  0,  1,  2,  6,  7,  5,  4, }, /* DDR0_DQ0[7:0] */
			.dq1 = { 12, 15, 14,  13, 8,  9, 10, 11 }, /* DDR0_DQ1[7:0] */
		},
		.ddr1 = {
			.dq0 = { 12,  15,  13,  14,  10,  8,  11,  9, }, /* DDR1_DQ0[7:0] */
			.dq1 = { 5, 6, 7, 4,  0, 3, 1, 2  }, /* DDR1_DQ1[7:0] */
		},
		.ddr2 = {
			.dq0 = { 2, 3, 0, 1,  7, 6, 5, 4, }, /* DDR2_DQ0[7:0] */
			.dq1 = { 12,  14,  15,  13,  10,  9,  8,  11  }, /* DDR2_DQ1[7:0] */
		},
		.ddr3 = {
			.dq0 = { 15, 12, 13, 14, 8, 9, 10,  11, }, /* DDR3_DQ0[7:0] */
			.dq1 = { 7,  6,  4,  5,  2,  0,  3,  1  }, /* DDR3_DQ1[7:0] */
		},
		.ddr4 = {
			.dq0 = { 6,  5,  4,  7,  0,  3,  2,  1, }, /* DDR4_DQ0[7:0] */
			.dq1 = { 15, 14,  13, 12, 11,  8, 9, 10 }, /* DDR4_DQ1[7:0] */
		},
		.ddr5 = {
			.dq0 = { 11,  9,  10,  8,  12,  14,  13,  15, }, /* DDR5_DQ0[7:0] */
			.dq1 = { 1, 0, 2, 3, 6, 7,  5,  4 }, /* DDR5_DQ1[7:0] */
		},
		.ddr6 = {
			.dq0 = { 2, 3, 0, 1, 5,  4, 6, 7, }, /* DDR6_DQ0[7:0] */
			.dq1 = { 13,  14,  15,  12,  11,  10,  8,  9  }, /* DDR6_DQ1[7:0] */
		},
		.ddr7 = {
			.dq0 = { 14, 13, 15,  12, 9, 8, 10, 11, }, /* DDR7_DQ0[7:0] */
			.dq1 = { 4,  5,  1,  2,  6,  0,  3,  7  }, /* DDR7_DQ1[7:0] */
		},
	},

	/* DQS CPU<>DRAM map */
	.lp4x_dqs_map = {
		.ddr0 = { .dqs0 = 0, .dqs1 = 1 },  /* DDR0_DQS[1:0] */
		.ddr1 = { .dqs0 = 1, .dqs1 = 0 },  /* DDR1_DQS[1:0] */
		.ddr2 = { .dqs0 = 0, .dqs1 = 1 },  /* DDR2_DQS[1:0] */
		.ddr3 = { .dqs0 = 1, .dqs1 = 0 },  /* DDR3_DQS[1:0] */
		.ddr4 = { .dqs0 = 0, .dqs1 = 1 },  /* DDR4_DQS[1:0] */
		.ddr5 = { .dqs0 = 1, .dqs1 = 0 },  /* DDR5_DQS[1:0] */
		.ddr6 = { .dqs0 = 0, .dqs1 = 1 },  /* DDR6_DQS[1:0] */
		.ddr7 = { .dqs0 = 1, .dqs1 = 0 },  /* DDR7_DQS[1:0] */
	},

	.ect = true, /* Enable Early Command Training */
};

const struct mb_cfg *variant_memory_params(void)
{
	return &board_memcfg;
}
