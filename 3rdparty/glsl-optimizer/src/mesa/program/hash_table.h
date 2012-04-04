/*
 * Copyright © 2008 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/**
 * \file hash_table.h
 * \brief Implementation of a generic, opaque hash table data type.
 *
 * \author Ian Romanick <ian.d.romanick@intel.com>
 */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

struct hash_table;

typedef unsigned (*hash_func_t)(const void *key);
typedef int (*hash_compare_func_t)(const void *key1, const void *key2);

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Hash table constructor
 *
 * Creates a hash table with the specified number of buckets.  The supplied
 * \c hash and \c compare routines are used when adding elements to the table
 * and when searching for elements in the table.
 *
 * \param num_buckets  Number of buckets (bins) in the hash table.
 * \param hash         Function used to compute hash value of input keys.
 * \param compare      Function used to compare keys.
 */
extern struct hash_table *hash_table_ctor(unsigned num_buckets,
    hash_func_t hash, hash_compare_func_t compare);


/**
 * Release all memory associated with a hash table
 *
 * \warning
 * This function cannot release memory occupied either by keys or data.
 */
extern void hash_table_dtor(struct hash_table *ht);


/**
 * Flush all entries from a hash table
 *
 * \param ht  Table to be cleared of its entries.
 */
extern void hash_table_clear(struct hash_table *ht);


/**
 * Search a hash table for a specific element
 *
 * \param ht   Table to be searched
 * \param key  Key of the desired element
 *
 * \return
 * The \c data value supplied to \c hash_table_insert when the element with
 * the matching key was added.  If no matching key exists in the table,
 * \c NULL is returned.
 */
extern void *hash_table_find(struct hash_table *ht, const void *key);


/**
 * Add an element to a hash table
 */
extern void hash_table_insert(struct hash_table *ht, void *data,
    const void *key);

/**
 * Remove a specific element from a hash table.
 */
extern void hash_table_remove(struct hash_table *ht, const void *key);

/**
 * Compute hash value of a string
 *
 * Computes the hash value of a string using the DJB2 algorithm developed by
 * Professor Daniel J. Bernstein.  It was published on comp.lang.c once upon
 * a time.  I was unable to find the original posting in the archives.
 *
 * \param key  Pointer to a NUL terminated string to be hashed.
 *
 * \sa hash_table_string_compare
 */
extern unsigned hash_table_string_hash(const void *key);


/**
 * Compare two strings used as keys
 *
 * This is just a macro wrapper around \c strcmp.
 *
 * \sa hash_table_string_hash
 */
#define hash_table_string_compare ((hash_compare_func_t) strcmp)


/**
 * Compute hash value of a pointer
 *
 * \param key  Pointer to be used as a hash key
 *
 * \note
 * The memory pointed to by \c key is \b never accessed.  The value of \c key
 * itself is used as the hash key
 *
 * \sa hash_table_pointer_compare
 */
unsigned
hash_table_pointer_hash(const void *key);


/**
 * Compare two pointers used as keys
 *
 * \sa hash_table_pointer_hash
 */
int
hash_table_pointer_compare(const void *key1, const void *key2);

void
hash_table_call_foreach(struct hash_table *ht,
			void (*callback)(const void *key,
					 void *data,
					 void *closure),
			void *closure);

#ifdef __cplusplus
}
#endif
#endif /* HASH_TABLE_H */
