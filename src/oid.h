/*
 * Copyright (C) the libgit2 contributors. All rights reserved.
 *
 * This file is part of libgit2, distributed under the GNU GPL v2 with
 * a Linking Exception. For full terms see the included COPYING file.
 */
#ifndef INCLUDE_oid_h__
#define INCLUDE_oid_h__

#include "common.h"

#include "git2/oid.h"

static git_oid git_oid__empty_blob_sha1 =
	{{ 0xe6, 0x9d, 0xe2, 0x9b, 0xb2, 0xd1, 0xd6, 0x43, 0x4b, 0x8b,
	   0x29, 0xae, 0x77, 0x5a, 0xd8, 0xc2, 0xe4, 0x8c, 0x53, 0x91 }};
static git_oid git_oid__empty_tree_sha1 =
	{{ 0x4b, 0x82, 0x5d, 0xc6, 0x42, 0xcb, 0x6e, 0xb9, 0xa0, 0x60,
	   0xe5, 0x4b, 0xf8, 0xd6, 0x92, 0x88, 0xfb, 0xee, 0x49, 0x04 }};

/**
 * Format a git_oid into a newly allocated c-string.
 *
 * The c-string is owned by the caller and needs to be manually freed.
 *
 * @param id the oid structure to format
 * @return the c-string; NULL if memory is exhausted. Caller must
 *			deallocate the string with git__free().
 */
char *git_oid_allocfmt(const git_oid *id);

GIT_INLINE(int) git_oid__hashcmp(const unsigned char *sha1, const unsigned char *sha2)
{
	return memcmp(sha1, sha2, GIT_OID_RAWSZ);
}

/*
 * Compare two oid structures.
 *
 * @param a first oid structure.
 * @param b second oid structure.
 * @return <0, 0, >0 if a < b, a == b, a > b.
 */
GIT_INLINE(int) git_oid__cmp(const git_oid *a, const git_oid *b)
{
	return git_oid__hashcmp(a->id, b->id);
}

GIT_INLINE(void) git_oid__cpy_prefix(
	git_oid *out, const git_oid *id, size_t len)
{
	memcpy(&out->id, id->id, (len + 1) / 2);

	if (len & 1)
		out->id[len / 2] &= 0xF0;
}

#endif
