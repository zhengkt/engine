/* Copyright (C) 2012-2020 Open Information Security Foundation
 *
 * You can copy, redistribute or modify this Program under the terms of
 * the GNU General Public License version 2 as published by the Free
 * Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

/**
 * \file
 *
 * \author Xavier Lange <xrlange@gmail.com>
 *
 */

#include "suricata-common.h"
#include "threads.h"
#include "decode.h"

#include "detect.h"
#include "detect-parse.h"
#include "detect-pkt-data.h"
#include "detect-engine.h"
#include "detect-engine-mpm.h"
#include "detect-engine-state.h"

#include "flow.h"
#include "flow-var.h"
#include "flow-util.h"

#include "util-debug.h"
#include "util-spm-bm.h"
#include "util-unittest.h"
#include "util-unittest-helper.h"

static int DetectPktDataSetup (DetectEngineCtx *, Signature *, const char *);
#ifdef UNITTESTS
static void DetectPktDataTestRegister(void);
#endif

/**
 * \brief Registration function for keyword: file_data
 */
void DetectPktDataRegister(void)
{
    sigmatch_table[DETECT_PKT_DATA].name = "pkt_data";
    sigmatch_table[DETECT_PKT_DATA].Setup = DetectPktDataSetup;
#ifdef UNITTESTS
    sigmatch_table[DETECT_PKT_DATA].RegisterTests = DetectPktDataTestRegister;
#endif
    sigmatch_table[DETECT_PKT_DATA].flags = SIGMATCH_NOOPT;
}

/**
 * \brief this function is used to parse pkt_data options
 * \brief into the current signature
 *
 * \param de_ctx pointer to the Detection Engine Context
 * \param s pointer to the current signature
 * \param unused unused for keyword with SIGMATCH_NOOPT set
 *
 * \retval 0 on Success
 * \retval -1 on Failure
 */
static int DetectPktDataSetup (DetectEngineCtx *de_ctx, Signature *s, const char *unused)
{
    SCEnter();
    if (s->init_data->transforms.cnt) {
        SCLogError("previous transforms not consumed before 'pkt_data'");
        SCReturnInt(-1);
    }
    s->init_data->list = DETECT_SM_LIST_NOTSET;
    SCReturnInt(0);
}

#ifdef UNITTESTS

/************************************Unittests*********************************/
static int DetectPktDataTest02(void)
{
    DetectEngineCtx *de_ctx = DetectEngineCtxInit();
    FAIL_IF_NULL(de_ctx);
    de_ctx->flags |= DE_QUIET;

    Signature *sig = DetectEngineAppendSig(de_ctx, "alert tcp any any -> any any "
                               "(file_data; compress_whitespace; "
                               " pkt_data; content:\"in pkt data\"; sid:1;)");
    FAIL_IF_NOT_NULL(sig);
    DetectEngineCtxFree(de_ctx);
    PASS;
}

static void DetectPktDataTestRegister(void)
{
    UtRegisterTest("DetectPktDataTest02", DetectPktDataTest02);
}
#endif
