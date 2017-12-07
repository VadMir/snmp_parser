/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/*
* last update: 2011-02-22
*
* mscu_hash.h : Hash Table
*
* Copyright (C) MSC, ORG 2007-2008
*/
// изменения
// ---------
// [*] 2015-06-22 Изменено: G-префикс заменен на TMSC для совместимости с glib
// [+] 2011-02-22 Добавлено: TMSCguint64HashTable
//

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <assert.h>
#include <stdlib.h>
#include <cstring>

#ifndef MSCULIB_HASH_H
#define MSCULIB_HASH_H

typedef guint           (*TMSCHashFunc)            (gconstpointer  key);
typedef void            (*TMSCHFunc)               (gpointer       key,
                                                 gpointer       value,
                                                 gpointer       user_data);
typedef gboolean        (*TMSCEqualFunc)           (gconstpointer  a,
                                                 gconstpointer  b);

typedef gboolean  (*TMSCHRFunc)  (gpointer  key,
                               gpointer  value,
                               gpointer  user_data);

typedef void            (*TMSCDestroyNotify)       (gpointer       data);
typedef void            (*TMSCFreeFunc)            (gpointer       data);

#define HASH_TABLE_CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

#define HASH_TABLE_MIN_SIZE 11
#define HASH_TABLE_MAX_SIZE 46727431

extern "C" MSCULIB_API guint g_spaced_primes_closest(guint num);


#define HASH_TABLE_RESIZE_UPPER_BOUND      13
#define HASH_TABLE_RESIZE_MULTIPLIER_BOUND 11
#define HASH_TABLE_RESIZE_LOWER_BOUND      9

extern "C" MSCULIB_API gconstpchar g_str_new(gconstpchar str);
extern "C" MSCULIB_API void g_str_destroy(void* str);

/**
* g_direct_hash:
* @v: a #gpointer key
*
* Converts a gpointer to a hash value.
* It can be passed to new() as the @hash_func parameter,
* when using pointers as keys in a #TMSCHashTable.
*
* Returns: a hash value corresponding to the key.
*/
extern "C" MSCULIB_API guint g_direct_hash(gconstpointer v);

/**
* g_direct_equal:
* @v1: a key.
* @v2: a key to compare with @v1.
*
* Compares two #gpointer arguments and returns %TRUE if they are equal.
* It can be passed to new() as the @key_equal_func
* parameter, when using pointers as keys in a #TMSCHashTable.
*
* Returns: %TRUE if the two keys match.
*/
extern "C" MSCULIB_API gboolean g_direct_equal(gconstpointer v1, gconstpointer v2);

/**
* g_int_equal:
* @v1: a pointer to a #gint key.
* @v2: a pointer to a #gint key to compare with @v1.
*
* Compares the two #gint values being pointed to and returns
* %TRUE if they are equal.
* It can be passed to new() as the @key_equal_func
* parameter, when using pointers to integers as keys in a #TMSCHashTable.
*
* Returns: %TRUE if the two keys match.
*/
extern "C" MSCULIB_API gboolean g_int_equal(gconstpointer v1, gconstpointer v2);

/**
* g_int_hash:
* @v: a pointer to a #gint key
*
* Converts a pointer to a #gint to a hash value.
* It can be passed to new() as the @hash_func parameter,
* when using pointers to integers values as keys in a #TMSCHashTable.
*
* Returns: a hash value corresponding to the key.
*/
extern "C" MSCULIB_API guint g_int_hash(gconstpointer v);

/**
* g_int_equal:
* @v1: a pointer to a #gint key.
* @v2: a pointer to a #gint key to compare with @v1.
*
* Compares the two #gint values being pointed to and returns
* %TRUE if they are equal.
* It can be passed to new() as the @key_equal_func
* parameter, when using pointers to integers as keys in a #TMSCHashTable.
*
* Returns: %TRUE if the two keys match.
*/
extern "C" MSCULIB_API gboolean g_int64_equal(gconstpointer v1, gconstpointer v2);

/**
* g_int_hash:
* @v: a pointer to a #gint key
*
* Converts a pointer to a #gint to a hash value.
* It can be passed to new() as the @hash_func parameter,
* when using pointers to integers values as keys in a #TMSCHashTable.
*
* Returns: a hash value corresponding to the key.
*/
extern "C" MSCULIB_API guint g_int64_hash(gconstpointer v);

/**
* g_str_equal:
* @v1: a key.
* @v2: a key to compare with @v1.
*
* Compares two strings for byte-by-byte equality and returns %TRUE
* if they are equal. It can be passed to new() as the
* @key_equal_func parameter, when using strings as keys in a #TMSCHashTable.
*
* Returns: %TRUE if the two keys match.
*/
extern "C" MSCULIB_API gboolean g_str_equal(gconstpointer v1, gconstpointer v2);

/**
* g_str_hash:
* @v: a string key.
*
* Converts a string to a hash value.
* It can be passed to new() as the @hash_func parameter,
* when using strings as keys in a #TMSCHashTable.
*
* Returns: a hash value corresponding to the key.
*/
extern "C" MSCULIB_API guint g_str_hash(gconstpointer v);

// 2017-07-27
extern "C" guint32 MSCULIB_API guint32_elf_hash(const unsigned char *s);

//////////////////////////////////////////////////////////////////////////
extern "C" MSCULIB_API void log_hash_table_insert_warning(gconstpchar hash_table_class, gconstpchar hash_table_name, gconstpchar hash_table_method, gsize_t nodes_in_row);

//////////////////////////////////////////////////////////////////////////
class LOCAL_API TMSCHashNode
{
public:
  TMSCHashNode(gpointer key, gpointer value, guint key_hash):
  key(key), value(value), key_hash(key_hash), next(0) {}

  gpointer   key;
  gpointer   value;
  TMSCHashNode *next;
  guint      key_hash;
};

extern "C" MSCULIB_API gpointer get_hash_node_mm();

class LOCAL_API TMSCHashTable
{
private:
  TMSCHashTable(const TMSCHashTable&):  mm_(get_hash_node_mm()) {};
  TMSCHashTable& operator=(const TMSCHashTable&) { return *this; };
public:
  /**
  * new_full:
  * @hash_func: a function to create a hash value from a key.
  * @key_equal_func: a function to check two keys for equality.
  * @key_destroy_func: a function to free the memory allocated for the key
  *   used when removing the entry from the #TMSCHashTable or %NULL if you
  *   don't want to supply such a function.
  * @value_destroy_func: a function to free the memory allocated for the
  *   value used when removing the entry from the #TMSCHashTable or %NULL if
  *   you don't want to supply such a function.
  *
  * Creates a new #TMSCHashTable like new() with a reference count
  * of 1 and allows to specify functions to free the memory allocated for the
  * key and value that get called when removing the entry from the #TMSCHashTable.
  *
  * Return value: a new #TMSCHashTable.
  **/
  TMSCHashTable(TMSCHashFunc hash_func, TMSCEqualFunc key_equal_func, TMSCDestroyNotify key_destroy_func = 0,  TMSCDestroyNotify value_destroy_func = 0, gconstpchar name = 0)
    :
    hash_func          (hash_func ? hash_func : g_direct_hash),
    key_equal_func     (key_equal_func),
    key_destroy_func   (key_destroy_func),
    value_destroy_func (value_destroy_func),
    mm_(get_hash_node_mm())
    ,name_(0)

  {
    size               = HASH_TABLE_MIN_SIZE;
    nnodes             = 0;
    nodes              = (TMSCHashNode**)calloc(size, sizeof(TMSCHashNode*));
    if (name != 0) {
      size_t l = strlen(name);
      name_ = (gpchar)malloc(l + 1);
      memmove(name_, name, l);
      name_[l] = 0;
    }
  }

  /**
  * destroy:
  *
  * Destroys all keys and values in the #TMSCHashTable and decrements its
  * reference count by 1. If keys and/or values are dynamically allocated,
  * you should either free them first or create the #TMSCHashTable with destroy
  * notifiers using new_full(). In the latter case the destroy
  * functions you supplied will be called on all keys and values during the
  * destruction phase.
  **/
  /*virtual */~TMSCHashTable()
  {
    remove_all();
    if (nodes)
      free(nodes);
    if (name_ != 0) {
      free(name_);
      name_ = 0;
    }
  }

  void RESIZE()
  {
    if ((size >= HASH_TABLE_RESIZE_UPPER_BOUND * nnodes &&
      size > HASH_TABLE_MIN_SIZE) ||
      (size <= HASH_TABLE_RESIZE_LOWER_BOUND * nnodes &&
      size < HASH_TABLE_MAX_SIZE))
      resize();
  }

  TMSCHashNode** lookup_node(gconstpointer key, guint *hash_return)
  {
    TMSCHashNode **node;
    guint hash_value;

    hash_value = (*hash_func)(key);
    node = &nodes[hash_value % size];

    if (hash_return)
      *hash_return = hash_value;

    /* Hash table lookup needs to be fast.
    *  We therefore remove the extra conditional of testing
    *  whether to call the key_equal_func or not from
    *  the inner loop.
    *
    *  Additional optimization: first check if our full hash
    *  values are equal so we can avoid calling the full-blown
    *  key equality function in most cases.
    */
    if (key_equal_func)
      while (*node && (((*node)->key_hash != hash_value) ||
        !(*key_equal_func) ((*node)->key, key)))
        node = &(*node)->next;
    else
      while (*node && (*node)->key != key)
        node = &(*node)->next;

    return node;
  }

  gsize_t nodes_in_place(gconstpointer key)
  {
    TMSCHashNode **node;
    guint hash_value = (*hash_func)(key);
    gsize_t node_count = 0;

    node = &nodes[hash_value % size];

    while (*node) {
      node = &(*node)->next;
      ++node_count;
    }

    return node_count;
  }

  /**
  * lookup:
  * @key: the key to look up.
  *
  * Looks up a key in a #TMSCHashTable. Note that this function cannot
  * distinguish between a key that is not present and one which is present
  * and has the value %NULL. If you need this distinction, use
  * lookup_extended().
  *
  * Return value: the associated value, or %NULL if the key is not found.
  **/
  gpointer lookup(gconstpointer key)
  {
    TMSCHashNode *node;

    node = *lookup_node(key, NULL);

    return node ? node->value : NULL;
  }

  /**
  * lookup_extended:
  * @lookup_key: the key to look up.
  * @orig_key: returns the original key.
  * @value: returns the value associated with the key.
  *
  * Looks up a key in the #TMSCHashTable, returning the original key and the
  * associated value and a #gboolean which is %TRUE if the key was found. This
  * is useful if you need to free the memory allocated for the original key,
  * for example before calling remove().
  *
  * Return value: %TRUE if the key was found in the #TMSCHashTable.
  **/
  gboolean lookup_extended (gconstpointer  lookup_key, gpointer      *orig_key, gpointer      *value)
  {
    TMSCHashNode *node;

    node = *lookup_node (lookup_key, NULL);

    if (node)
    {
      if (orig_key)
        *orig_key = node->key;
      if (value)
        *value = node->value;
      return true;
    }
    else
      return false;
  }

  /**
  * insert:
  * @key: a key to insert.
  * @value: the value to associate with the key.
  *
  * Inserts a new key and value into a #TMSCHashTable.
  *
  * If the key already exists in the #TMSCHashTable its current value is replaced
  * with the new value. If you supplied a @value_destroy_func when creating the
  * #TMSCHashTable, the old value is freed using that function. If you supplied
  * a @key_destroy_func when creating the #TMSCHashTable, the passed key is freed
  * using that function.
  **/
  void insert(gpointer key, gpointer value)
  {
    TMSCHashNode **node;
    guint key_hash;

    node = lookup_node(key, &key_hash);

    if (*node) {
      /* do not reset node->key in this place, keeping
      * the old key is the intended behavior.
      * replace() can be used instead.
      */

      /* free the passed key */
      if (key_destroy_func)
        key_destroy_func (key);

      if (value_destroy_func)
        value_destroy_func ((*node)->value);

      (*node)->key = key;
      (*node)->value = value;
    } else {
      gsize_t nip = nodes_in_place(key);
      if (nip > 16)
        log_hash_table_insert_warning("TMSCHashTable", name_, "insert", nip);

  //!!!       *node = new TMSCHashNode(key, value, key_hash);
      *node = (TMSCHashNode*)memory_manager_alloc(mm_);
      (*node)->key = key;
      (*node)->value = value;
      (*node)->key_hash = key_hash;
      (*node)->next = 0;

      nnodes++;
      RESIZE();
    }
  }

  /**
  * replace:
  * @key: a key to insert.
  * @value: the value to associate with the key.
  *
  * Inserts a new key and value into a #TMSCHashTable similar to
  * insert(). The difference is that if the key already exists
  * in the #TMSCHashTable, it gets replaced by the new key. If you supplied a
  * @value_destroy_func when creating the #TMSCHashTable, the old value is freed
  * using that function. If you supplied a @key_destroy_func when creating the
  * #TMSCHashTable, the old key is freed using that function.
  **/
  void
    replace (gpointer    key, gpointer    value)
  {
    TMSCHashNode **node;
    guint key_hash;

    node = lookup_node(key, &key_hash);

    if (*node)
    {
      if (key_destroy_func)
        key_destroy_func ((*node)->key);

      if (value_destroy_func)
        value_destroy_func ((*node)->value);

      (*node)->key   = key;
      (*node)->value = value;
    }
    else
    {
      //!!!       *node = new TMSCHashNode(key, value, key_hash);
      *node = (TMSCHashNode*)memory_manager_alloc(mm_);
      (*node)->key = key;
      (*node)->value = value;
      (*node)->key_hash = key_hash;
      (*node)->next = 0;

      nnodes++;
      RESIZE();
    }
  }

  /**
  * remove:
  * @key: the key to remove.
  *
  * Removes a key and its associated value from a #TMSCHashTable.
  *
  * If the #TMSCHashTable was created using new_full(), the
  * key and value are freed using the supplied destroy functions, otherwise
  * you have to make sure that any dynamically allocated values are freed
  * yourself.
  *
  * Return value: %TRUE if the key was found and removed from the #TMSCHashTable.
  **/
  gboolean remove (gconstpointer  key)
  {
    TMSCHashNode **node, *dest;

    node = lookup_node (key, NULL);
    if (*node)
    {
      dest = *node;
      (*node) = dest->next;
      g_hash_node_destroy (dest,
        key_destroy_func,
        value_destroy_func);
      nnodes--;

      RESIZE();

      return true;
    }

    return false;
  }

  /**
  * remove_all:
  *
  * Removes all keys and their associated values from a #TMSCHashTable.
  *
  * If the #TMSCHashTable was created using new_full(), the keys
  * and values are freed using the supplied destroy functions, otherwise you
  * have to make sure that any dynamically allocated values are freed
  * yourself.
  *
  * Since: 2.12
  **/
  void remove_all ()
  {
    guint i;

    for (i = 0; i < size; i++)
    {
      g_hash_nodes_destroy (nodes[i],
        key_destroy_func,
        value_destroy_func);
      nodes[i] = NULL;
    }
    nnodes = 0;

    RESIZE();
  }

  /**
  * steal:
  * @key: the key to remove.
  *
  * Removes a key and its associated value from a #TMSCHashTable without
  * calling the key and value destroy functions.
  *
  * Return value: %TRUE if the key was found and removed from the #TMSCHashTable.
  **/
  gboolean steal (gconstpointer  key)
  {
    TMSCHashNode **node, *dest;

    node = lookup_node(key, NULL);
    if (*node)
    {
      dest = *node;
      (*node) = dest->next;
      g_hash_node_destroy (dest, NULL, NULL);
      nnodes--;

      RESIZE();

      return true;
    }

    return false;
  }

  /**
  * steal_all:
  *
  * Removes all keys and their associated values from a #TMSCHashTable
  * without calling the key and value destroy functions.
  *
  * Since: 2.12
  **/
  void steal_all ()
  {
    guint i;

    for (i = 0; i < size; i++)
    {
      g_hash_nodes_destroy (nodes[i], NULL, NULL);
      nodes[i] = NULL;
    }

    nnodes = 0;

    RESIZE();
  }

  /**
  * foreach_remove:
  * @func: the function to call for each key/value pair.
  * @user_data: user data to pass to the function.
  *
  * Calls the given function for each key/value pair in the #TMSCHashTable.
  * If the function returns %TRUE, then the key/value pair is removed from the
  * #TMSCHashTable. If you supplied key or value destroy functions when creating
  * the #TMSCHashTable, they are used to free the memory allocated for the removed
  * keys and values.
  *
  * Return value: the number of key/value pairs removed.
  **/
  guint foreach_remove (TMSCHRFunc   func, gpointer  user_data)
  {
    assert(func != NULL);

    return foreach_remove_or_steal(func, user_data, true);
  }

  /**
  * foreach_steal:
  * @func: the function to call for each key/value pair.
  * @user_data: user data to pass to the function.
  *
  * Calls the given function for each key/value pair in the #TMSCHashTable.
  * If the function returns %TRUE, then the key/value pair is removed from the
  * #TMSCHashTable, but no key or value destroy functions are called.
  *
  * Return value: the number of key/value pairs removed.
  **/
  guint foreach_steal (TMSCHRFunc func, gpointer  user_data)
  {
    assert(func != 0);

    return foreach_remove_or_steal(func, user_data, false);
  }

  guint foreach_remove_or_steal (TMSCHRFunc   func, gpointer    user_data, gboolean    notify)
  {
    TMSCHashNode *node, *prev;
    guint deleted = 0;

    for (guint i = 0; i < size; i++)
    {
restart:

      prev = NULL;

      for (node = nodes[i]; node; prev = node, node = node->next)
      {
        if ((* func) (node->key, node->value, user_data))
        {
          deleted += 1;

          nnodes -= 1;

          if (prev)
          {
            prev->next = node->next;
            g_hash_node_destroy (node,
              notify ? key_destroy_func : NULL,
              notify ? value_destroy_func : NULL);
            node = prev;
          }
          else
          {
            nodes[i] = node->next;
            g_hash_node_destroy (node,
              notify ? key_destroy_func : NULL,
              notify ? value_destroy_func : NULL);
            goto restart;
          }
        }
      }
    }

    RESIZE();

    return deleted;
  }

  /**
  * foreach:
  * @func: the function to call for each key/value pair.
  * @user_data: user data to pass to the function.
  *
  * Calls the given function for each of the key/value pairs in the
  * #TMSCHashTable.  The function is passed the key and value of each
  * pair, and the given @user_data parameter.  The hash table may not
  * be modified while iterating over it (you can't add/remove
  * items). To remove all items matching a predicate, use
  * foreach_remove().
  **/
  void foreach_simple (TMSCHFunc    func, gpointer    user_data)
  {
    TMSCHashNode *node;

    assert(func != 0);

    for (guint i = 0; i < size; i++)
      for (node = nodes[i]; node; node = node->next)
        (* func) (node->key, node->value, user_data);
  }

  /**
  * find:
  * @predicate:  function to test the key/value pairs for a certain property.
  * @user_data:  user data to pass to the function.
  *
  * Calls the given function for key/value pairs in the #TMSCHashTable until
  * @predicate returns %TRUE.  The function is passed the key and value of
  * each pair, and the given @user_data parameter. The hash table may not
  * be modified while iterating over it (you can't add/remove items).
  *
  * Return value: The value of the first key/value pair is returned, for which
  * func evaluates to %TRUE. If no pair with the requested property is found,
  * %NULL is returned.
  *
  * Since: 2.4
  **/
  gpointer find(TMSCHRFunc predicate, gpointer user_data)
  {
    TMSCHashNode *node;

    assert(predicate != 0);

    for (guint i = 0; i < size; i++)
      for (node = nodes[i]; node; node = node->next)
        if (predicate (node->key, node->value, user_data))
          return node->value;
    return NULL;
  }

  /**
  * size:
  *
  * Returns the number of elements contained in the #TMSCHashTable.
  *
  * Return value: the number of key/value pairs in the #TMSCHashTable.
  **/
  guint get_size()
  {
    return nnodes;
  }

  void resize()
  {
    TMSCHashNode **new_nodes;
    TMSCHashNode *node;
    TMSCHashNode *next;
    guint hash_val;
    guint new_size;

    new_size = g_spaced_primes_closest(nnodes * HASH_TABLE_RESIZE_MULTIPLIER_BOUND);
    new_size = HASH_TABLE_CLAMP (new_size, HASH_TABLE_MIN_SIZE, HASH_TABLE_MAX_SIZE);

    if (new_size == size) // we have no new primes
      return;

    new_nodes = (TMSCHashNode**)calloc(new_size, sizeof(TMSCHashNode*));

    for (guint i = 0; i < size; i++)
      for (node = nodes[i]; node; node = next)
      {
        next = node->next;

        hash_val = node->key_hash % new_size;

        node->next = new_nodes[hash_val];
        new_nodes[hash_val] = node;
      }

      free(nodes);
      nodes = new_nodes;
      size = new_size;
  }

  void g_hash_node_destroy(TMSCHashNode *hash_node, TMSCDestroyNotify key_destroy_func, TMSCDestroyNotify value_destroy_func)
  {
    if (key_destroy_func)
      key_destroy_func (hash_node->key);
    if (value_destroy_func)
      value_destroy_func (hash_node->value);
    //!!!     delete hash_node;
    memory_manager_free(mm_, hash_node);
  }

  void g_hash_nodes_destroy(TMSCHashNode *hash_node, TMSCFreeFunc key_destroy_func, TMSCFreeFunc value_destroy_func)
  {
    while (hash_node)
    {
      TMSCHashNode *next = hash_node->next;
      if (key_destroy_func)
        key_destroy_func (hash_node->key);
      if (value_destroy_func)
        value_destroy_func (hash_node->value);
      //!!!     delete hash_node;
      memory_manager_free(mm_, hash_node);
      hash_node = next;
    }
  }

private:
  gpchar           name_;
  guint            size;
  guint            nnodes;
  TMSCHashNode      **nodes;
  TMSCHashFunc        hash_func;
  TMSCEqualFunc       key_equal_func;
  TMSCDestroyNotify   key_destroy_func;
  TMSCDestroyNotify   value_destroy_func;
  gpointer mm_;
};


//////////////////////////////////////////////////////////////////////////
class LOCAL_API TMSCguint32HashNode
{
public:
  TMSCguint32HashNode(guint32 key, guint32 value, guint key_hash):
    key(key), value(value), key_hash(key_hash), next(0) {}

  guint32   key;
  guint32   value;
  TMSCguint32HashNode *next;
  guint      key_hash;
};

class LOCAL_API TMSCguint32HashTable
{
private:
  TMSCguint32HashTable(const TMSCguint32HashTable&) {}
  TMSCguint32HashTable& operator=(const TMSCguint32HashTable&) { return *this; }
public:
  TMSCguint32HashTable(gconstpchar name = 0): name_(0)
  {
    size               = HASH_TABLE_MIN_SIZE;
    nnodes             = 0;
    nodes              = (TMSCguint32HashNode**)calloc(size, sizeof(TMSCguint32HashNode*));
    if (name != 0) {
      size_t l = strlen(name);
      name_ = (gpchar)malloc(l + 1);
      memmove(name_, name, l);
      name_[l] = 0;
    }
  }

  /*virtual*/ ~TMSCguint32HashTable()
  {
    remove_all();
    if (nodes)
      free(nodes);
    if (name_ != 0) {
      free(name_);
      name_ = 0;
    }
  }

  void RESIZE()
  {
    if ((size >= HASH_TABLE_RESIZE_UPPER_BOUND * nnodes && size > HASH_TABLE_MIN_SIZE) ||
      (size <= HASH_TABLE_RESIZE_LOWER_BOUND * nnodes && size < HASH_TABLE_MAX_SIZE))
      resize();
  }

  TMSCguint32HashNode** lookup_node (guint32 key, guint *hash_return)
  {
    TMSCguint32HashNode **node;
    guint hash_value;

    hash_value = key;
    node = &nodes[hash_value % size];

    if (hash_return)
      *hash_return = hash_value;

    while (*node && (*node)->key != key)
      node = &(*node)->next;

    return node;
  }

  gsize_t nodes_in_place(guint32 key)
  {
    TMSCguint32HashNode **node;
    guint hash_value = key;
    gsize_t node_count = 0;

    node = &nodes[hash_value % size];

    while (*node) {
      node = &(*node)->next;
      ++node_count;
    }

    return node_count;
  }

  guint32 lookup(guint32 key)
  {
    if (!nodes)
      return 0;

    TMSCguint32HashNode *node;

    node = *lookup_node(key, NULL);

    return node ? node->value : 0;
  }

  gboolean lookup_extended(guint32  lookup_key,
    guint32      *orig_key,
    guint32      *value)
  {
    if (!nodes)
      return false;

    TMSCguint32HashNode *node;

    node = *lookup_node (lookup_key, NULL);

    if (node) {
      if (orig_key)
        *orig_key = node->key;
      if (value)
        *value = node->value;
      return true;
    }
    else
      return false;
  }

  void insert(guint32  key, guint32  value)
  {
    if (!nodes)
      resize();

    TMSCguint32HashNode **node;
    guint key_hash;

    node = lookup_node(key, &key_hash);

    if (*node) {
      /* do not reset node->key in this place, keeping
      * the old key is the intended behavior.
      * replace() can be used instead.
      */

  //     (*node)->key = key;
      (*node)->value = value;
    } else {
      gsize_t nip = nodes_in_place(key);
      if (nip > 16)
        log_hash_table_insert_warning("TMSCguint32HashTable", name_, "insert", nip);

      *node = new TMSCguint32HashNode(key, value, key_hash);

      nnodes++;
      RESIZE();
    }
  }

  void replace(guint32 key, guint32 value)
  {
    if (!nodes)
      resize();

    TMSCguint32HashNode **node;
    guint key_hash;

    node = lookup_node(key, &key_hash);

    if (*node)
    {
      (*node)->key   = key;
      (*node)->value = value;
    }
    else
    {
      *node = new TMSCguint32HashNode(key, value, key_hash);
      nnodes++;
      RESIZE();
    }
  }

  gboolean remove(guint32 key)
  {
    if (!nodes)
      return false;

    TMSCguint32HashNode **node, *dest;

    node = lookup_node (key, NULL);
    if (*node)
    {
      dest = *node;
      (*node) = dest->next;
      g_hash_node_destroy (dest);
      nnodes--;

      RESIZE();

      return true;
    }

    return false;
  }

  void remove_all()
  {
    if (!nodes)
      return;

    guint i;

    for (i = 0; i < size; i++)
    {
      g_hash_nodes_destroy (nodes[i]);
      nodes[i] = NULL;
    }
    nnodes = 0;

    RESIZE();
  }

  gboolean steal(guint32 key)
  {
    if (!nodes)
      return false;

    TMSCguint32HashNode **node, *dest;

    node = lookup_node(key, NULL);
    if (*node)
    {
      dest = *node;
      (*node) = dest->next;
      g_hash_node_destroy (dest);
      nnodes--;

      RESIZE();

      return true;
    }

    return false;
  }

  void steal_all()
  {
    if (!nodes)
      return;

    guint i;

    for (i = 0; i < size; i++)
    {
      g_hash_nodes_destroy (nodes[i]);
      nodes[i] = NULL;
    }

    nnodes = 0;

    RESIZE();
  }

  guint foreach_remove(TMSCHRFunc   func, gpointer  user_data)
  {
    assert(func != NULL);

    return foreach_remove_or_steal(func, user_data/*, TRUE*/);
  }

  guint foreach_steal(TMSCHRFunc func, gpointer  user_data)
  {
    assert(func != 0);

    return foreach_remove_or_steal(func, user_data/*, FALSE*/);
  }

  guint foreach_remove_or_steal(TMSCHRFunc   func, gpointer    user_data/*, gboolean    notify*/)
  {
    if (!nodes)
      return 0;

    TMSCguint32HashNode *node, *prev;
    guint deleted = 0;

    for (guint i = 0; i < size; i++)
    {
restart:

      prev = NULL;

      for (node = nodes[i]; node; prev = node, node = node->next)
      {
        if ((* func) ((gpointer)(intptr_t)node->key, (gpointer)(intptr_t)node->value, user_data))
        {
          deleted += 1;

          nnodes -= 1;

          if (prev)
          {
            prev->next = node->next;
            g_hash_node_destroy (node);
            node = prev;
          }
          else
          {
            nodes[i] = node->next;
            g_hash_node_destroy (node);
            goto restart;
          }
        }
      }
    }

    RESIZE();

    return deleted;
  }

  void foreach_simple(TMSCHFunc    func, gpointer    user_data)
  {
    if (!nodes)
      return;

    TMSCguint32HashNode *node;

    assert(func != 0);

    for (guint i = 0; i < size; i++)
      for (node = nodes[i]; node; node = node->next)
        (* func) ((gpointer)(intptr_t)node->key, (gpointer)(intptr_t)node->value, user_data);
  }

  guint32 find(TMSCHRFunc      predicate, gpointer     user_data)
  {
    if (!nodes)
      return 0;

    TMSCguint32HashNode *node;

    assert(predicate != 0);

    for (guint i = 0; i < size; i++)
      for (node = nodes[i]; node; node = node->next)
        if (predicate ((gpointer)(intptr_t)node->key, (gpointer)(intptr_t)node->value, user_data))
          return node->value;
    return 0;
  }

  guint get_size()
  {
    return nnodes;
  }

  void resize()
  {
    TMSCguint32HashNode **new_nodes;
    TMSCguint32HashNode *node;
    TMSCguint32HashNode *next;
    guint hash_val;
    guint new_size;

    new_size = g_spaced_primes_closest(nnodes * HASH_TABLE_RESIZE_MULTIPLIER_BOUND);
    new_size = HASH_TABLE_CLAMP (new_size, HASH_TABLE_MIN_SIZE, HASH_TABLE_MAX_SIZE);

    if (new_size == size) // we have no new primes
      return;

    new_nodes = (TMSCguint32HashNode**)calloc(new_size, sizeof(TMSCguint32HashNode*));

    for (guint i = 0; i < size; i++)
      for (node = nodes[i]; node; node = next)
      {
        next = node->next;

        hash_val = node->key_hash % new_size;

        node->next = new_nodes[hash_val];
        new_nodes[hash_val] = node;
      }

      free(nodes);
      nodes = new_nodes;
      size = new_size;
  }

  void g_hash_node_destroy(TMSCguint32HashNode *hash_node)
  {
    delete hash_node;
  }

  void g_hash_nodes_destroy(TMSCguint32HashNode *hash_node)
  {
    while (hash_node)
    {
      TMSCguint32HashNode *next = hash_node->next;
      delete hash_node;
      hash_node = next;
    }
  }

private:
  gpchar           name_;
  guint            size;
  guint            nnodes;
  TMSCguint32HashNode      **nodes;
};

//////////////////////////////////////////////////////////////////////////
class LOCAL_API TMSCguint64HashNode
{
public:
  TMSCguint64HashNode(/*guint64*/unsigned long long  key, guint64 value, guint key_hash):
    key(key), value(value), key_hash(key_hash), next(0) {}

  /*guint64*/unsigned long long   key;
  guint64   value;
  TMSCguint64HashNode *next;
  guint      key_hash;
};

class LOCAL_API TMSCguint64HashTable
{
private:
  TMSCguint64HashTable(const TMSCguint64HashTable&) {}
  TMSCguint64HashTable& operator=(const TMSCguint64HashTable&) { return *this; }
public:
  TMSCguint64HashTable(gconstpchar name = 0): name_(0)
  {
    size               = HASH_TABLE_MIN_SIZE;
    nnodes             = 0;
    nodes              = (TMSCguint64HashNode**)calloc(size, sizeof(TMSCguint64HashNode*));
    if (name != 0) {
      size_t l = strlen(name);
      name_ = (gpchar)malloc(l + 1);
      memmove(name_, name, l);
      name_[l] = 0;
    }
  }

  /*virtual*/ ~TMSCguint64HashTable()
  {
    remove_all();
    if (nodes)
      free(nodes);
    if (name_ != 0) {
      free(name_);
      name_ = 0;
    }
  }

  void RESIZE()
  {
    if ((size >= HASH_TABLE_RESIZE_UPPER_BOUND * nnodes &&
      size > HASH_TABLE_MIN_SIZE) ||
      (size <= HASH_TABLE_RESIZE_LOWER_BOUND * nnodes &&
      size < HASH_TABLE_MAX_SIZE))
      resize();
  }

  TMSCguint64HashNode** lookup_node (guint64 key, guint *hash_return)
  {
    TMSCguint64HashNode **node;
    guint hash_value;

    hash_value = ((key & 0xffffffff) + (key >> 32)) & 0xffffffff;
    node = &nodes[hash_value % size];

    if (hash_return)
      *hash_return = hash_value;

    while (*node && (*node)->key != key)
      node = &(*node)->next;

    return node;
  }

  gsize_t nodes_in_place(guint64 key)
  {
    TMSCguint64HashNode **node;
    guint hash_value = ((key & 0xffffffff) + (key >> 32)) & 0xffffffff;
    gsize_t node_count = 0;

    node = &nodes[hash_value % size];

    while (*node) {
      node = &(*node)->next;
      ++node_count;
    }

    return node_count;
  }

  guint64 lookup(guint64 key)
  {
    if (!nodes)
      return 0;

    TMSCguint64HashNode *node;

    node = *lookup_node(key, NULL);

    return node ? node->value : 0;
  }

  gboolean lookup_extended(guint64  lookup_key,
    guint64      *orig_key,
    guint64      *value)
  {
    if (!nodes)
      return false;

    TMSCguint64HashNode *node;

    node = *lookup_node (lookup_key, NULL);

    if (node)
    {
      if (orig_key)
        *orig_key = node->key;
      if (value)
        *value = node->value;
      return true;
    }
    else
      return false;
  }

  void insert(guint64  key, guint64 value)
  {
    if (!nodes)
      resize();

    TMSCguint64HashNode **node;
    guint key_hash;

    node = lookup_node(key, &key_hash);

    if (*node) {
      /* do not reset node->key in this place, keeping
      * the old key is the intended behavior.
      * replace() can be used instead.
      */

  //     (*node)->key = key;
      (*node)->value = value;
    } else {
      gsize_t nip = nodes_in_place(key);
      if (nip > 16)
        log_hash_table_insert_warning("TMSCguint64HashTable", name_, "insert", nip);

      *node = new TMSCguint64HashNode(key, value, key_hash);

      nnodes++;
      RESIZE();
    }
  }

  void replace(guint64 key, guint64 value)
  {
    if (!nodes)
      resize();

    TMSCguint64HashNode **node;
    guint key_hash;

    node = lookup_node(key, &key_hash);

    if (*node)
    {
      (*node)->key   = key;
      (*node)->value = value;
    }
    else
    {
      *node = new TMSCguint64HashNode(key, value, key_hash);
      nnodes++;
      RESIZE();
    }
  }

  gboolean remove(guint64 key)
  {
    if (!nodes)
      return false;

    TMSCguint64HashNode **node, *dest;

    node = lookup_node (key, NULL);
    if (*node)
    {
      dest = *node;
      (*node) = dest->next;
      g_hash_node_destroy (dest);
      nnodes--;

      RESIZE();

      return true;
    }

    return false;
  }

  void remove_all()
  {
    if (!nodes)
      return;

    guint i;

    for (i = 0; i < size; i++)
    {
      g_hash_nodes_destroy (nodes[i]);
      nodes[i] = NULL;
    }
    nnodes = 0;

    RESIZE();
  }

  gboolean steal(guint64 key)
  {
    if (!nodes)
      return false;

    TMSCguint64HashNode **node, *dest;

    node = lookup_node(key, NULL);
    if (*node)
    {
      dest = *node;
      (*node) = dest->next;
      g_hash_node_destroy (dest);
      nnodes--;

      RESIZE();

      return true;
    }

    return false;
  }

  void steal_all()
  {
    if (!nodes)
      return;

    guint i;

    for (i = 0; i < size; i++)
    {
      g_hash_nodes_destroy (nodes[i]);
      nodes[i] = NULL;
    }

    nnodes = 0;

    RESIZE();
  }

  guint foreach_remove(TMSCHRFunc   func, gpointer  user_data)
  {
    assert(func != NULL);

    return foreach_remove_or_steal(func, user_data/*, TRUE*/);
  }

  guint foreach_steal(TMSCHRFunc func, gpointer  user_data)
  {
    assert(func != 0);

    return foreach_remove_or_steal(func, user_data/*, FALSE*/);
  }

  guint foreach_remove_or_steal(TMSCHRFunc   func, gpointer    user_data/*, gboolean    notify*/)
  {
    if (!nodes)
      return 0;

    TMSCguint64HashNode *node, *prev;
    guint deleted = 0;

    for (guint i = 0; i < size; i++)
    {
restart:

      prev = NULL;

      for (node = nodes[i]; node; prev = node, node = node->next)
      {
        if ((* func) ((gpointer)node->key, (gpointer)node->value, user_data))
        {
          deleted += 1;

          nnodes -= 1;

          if (prev)
          {
            prev->next = node->next;
            g_hash_node_destroy (node);
            node = prev;
          }
          else
          {
            nodes[i] = node->next;
            g_hash_node_destroy (node);
            goto restart;
          }
        }
      }
    }

    RESIZE();

    return deleted;
  }

  void foreach_simple(TMSCHFunc    func, gpointer    user_data)
  {
    if (!nodes)
      return;

    TMSCguint64HashNode *node;

    assert(func != 0);

    for (guint i = 0; i < size; i++)
      for (node = nodes[i]; node; node = node->next)
        (* func) ((gpointer)node->key, (gpointer)node->value, user_data);
  }

  guint64 find(TMSCHRFunc      predicate, gpointer     user_data)
  {
    if (!nodes)
      return 0;

    TMSCguint64HashNode *node;

    assert(predicate != 0);

    for (guint i = 0; i < size; i++)
      for (node = nodes[i]; node; node = node->next)
        if (predicate ((gpointer)node->key, (gpointer)node->value, user_data))
          return node->value;
    return 0;
  }

  guint get_size()
  {
    return nnodes;
  }

  void resize()
  {
    TMSCguint64HashNode **new_nodes;
    TMSCguint64HashNode *node;
    TMSCguint64HashNode *next;
    guint hash_val;
    guint new_size;

    new_size = g_spaced_primes_closest(nnodes * HASH_TABLE_RESIZE_MULTIPLIER_BOUND);
    new_size = HASH_TABLE_CLAMP (new_size, HASH_TABLE_MIN_SIZE, HASH_TABLE_MAX_SIZE);

    if (new_size == size) // we have no new primes
      return;

    new_nodes = (TMSCguint64HashNode**)calloc(new_size, sizeof(TMSCguint64HashNode*));

    for (guint i = 0; i < size; i++)
      for (node = nodes[i]; node; node = next)
      {
        next = node->next;

        hash_val = node->key_hash % new_size;

        node->next = new_nodes[hash_val];
        new_nodes[hash_val] = node;
      }

      free(nodes);
      nodes = new_nodes;
      size = new_size;
  }

  void g_hash_node_destroy(TMSCguint64HashNode *hash_node)
  {
    delete hash_node;
  }

  void g_hash_nodes_destroy(TMSCguint64HashNode *hash_node)
  {
    while (hash_node)
    {
      TMSCguint64HashNode *next = hash_node->next;
      delete hash_node;
      hash_node = next;
    }
  }

private:
  gpchar           name_;
  guint            size;
  guint            nnodes;
  TMSCguint64HashNode      **nodes;
};

//////////////////////////////////////////////////////////////////////////
class LOCAL_API TMSCdirectHashNode
{
public:
  TMSCdirectHashNode(gpointer key, gpointer value, guint key_hash):
    key(key), value(value), key_hash(key_hash), next(0) {}

  gpointer   key;
  gpointer   value;
  TMSCdirectHashNode *next;
  guint      key_hash;
};

class LOCAL_API TMSCdirectHashTable
{
private:
  TMSCdirectHashTable(const TMSCdirectHashTable&) {}
  TMSCdirectHashTable& operator=(const TMSCdirectHashTable&) { return *this; }
public:
  TMSCdirectHashTable(gconstpchar name = 0): name_(0)
  {
    size               = HASH_TABLE_MIN_SIZE;
    nnodes             = 0;
    nodes              = (TMSCdirectHashNode**)calloc(size, sizeof(TMSCdirectHashNode*));
    if (name != 0) {
      size_t l = strlen(name);
      name_ = (gpchar)malloc(l + 1);
      memmove(name_, name, l);
      name_[l] = 0;
    }
  }

  /*virtual*/ ~TMSCdirectHashTable()
  {
    remove_all();
    if (nodes)
      free(nodes);
    if (name_ != 0) {
      free(name_);
      name_ = 0;
    }
  }

  void RESIZE()
  {
    if ((size >= HASH_TABLE_RESIZE_UPPER_BOUND * nnodes &&
      size > HASH_TABLE_MIN_SIZE) ||
      (size <= HASH_TABLE_RESIZE_LOWER_BOUND * nnodes &&
      size < HASH_TABLE_MAX_SIZE))
      resize();
  }

  TMSCdirectHashNode** lookup_node (gpointer key, guint *hash_return)
  {
    TMSCdirectHashNode **node;
    guint hash_value;

		guint64 key64 = (guint64)key;
		hash_value = ((key64 & 0xffffffff) + (key64 >> 32)) & 0xffffffff;
//     if (sizeof(gpointer) > sizeof(guint32))
// 			hash_value = (((gsize_t)key & 0xffffffff) + ((gsize_t)key >> 32)) & 0xffffffff;
//     else
// 			hash_value = (gsize_t)key & 0xffffffff;
    node = &nodes[hash_value % size];

    if (hash_return)
      *hash_return = hash_value;

    while (*node && (*node)->key != key)
      node = &(*node)->next;

    return node;
  }

  gsize_t nodes_in_place(gpointer key)
  {
    TMSCdirectHashNode **node;
    guint hash_value;

		guint64 key64 = (guint64)key;
		hash_value = ((key64 & 0xffffffff) + (key64 >> 32)) & 0xffffffff;
//     if (sizeof(gpointer) > sizeof(guint32))
//       hash_value = (((size_t)key & 0xffffffff) + ((size_t)key >> 32)) & 0xffffffff;
//     else
//       hash_value = (size_t)key & 0xffffffff;
    gsize_t node_count = 0;

    node = &nodes[hash_value % size];

    while (*node) {
      node = &(*node)->next;
      ++node_count;
    }

    return node_count;
  }

  gpointer lookup(gpointer key)
  {
    if (!nodes)
      return 0;

    TMSCdirectHashNode *node;

    node = *lookup_node(key, NULL);

    return node ? node->value : NULL;
  }

  gboolean lookup_extended(gpointer lookup_key, gpointer *orig_key, gpointer *value)
  {
    if (!nodes)
      return false;

    TMSCdirectHashNode *node;

    node = *lookup_node (lookup_key, NULL);

    if (node)
    {
      if (orig_key)
        *orig_key = node->key;
      if (value)
        *value = node->value;
      return true;
    }
    else
      return false;
  }

  void insert(gpointer  key, gpointer  value)
  {
    if (!nodes)
      resize();

    TMSCdirectHashNode **node;
    guint key_hash;

    node = lookup_node(key, &key_hash);

    if (*node) {
      /* do not reset node->key in this place, keeping
      * the old key is the intended behavior.
      * replace() can be used instead.
      */

  //     (*node)->key = key;
      (*node)->value = value;
    } else {
      gsize_t nip = nodes_in_place(key);
      if (nip > 16)
        log_hash_table_insert_warning("TMSCdirectHashTable", name_, "insert", nip);

      *node = new TMSCdirectHashNode(key, value, key_hash);

      nnodes++;
      RESIZE();
    }
  }

  void replace(gpointer key, gpointer value)
  {
    if (!nodes)
      resize();

    TMSCdirectHashNode **node;
    guint key_hash;

    node = lookup_node(key, &key_hash);

    if (*node)
    {
      (*node)->key   = key;
      (*node)->value = value;
    }
    else
    {
      *node = new TMSCdirectHashNode(key, value, key_hash);
      nnodes++;
      RESIZE();
    }
  }

  gboolean remove(gpointer key)
  {
    if (!nodes)
      return false;

    TMSCdirectHashNode **node, *dest;

    node = lookup_node (key, NULL);
    if (*node)
    {
      dest = *node;
      (*node) = dest->next;
      g_hash_node_destroy (dest);
      nnodes--;

      RESIZE();

      return true;
    }

    return false;
  }

  void remove_all()
  {
    if (!nodes)
      return;

    guint i;

    for (i = 0; i < size; i++)
    {
      g_hash_nodes_destroy (nodes[i]);
      nodes[i] = NULL;
    }
    nnodes = 0;

    RESIZE();
  }

  gboolean steal(gpointer key)
  {
    if (!nodes)
      return false;

    TMSCdirectHashNode **node, *dest;

    node = lookup_node(key, NULL);
    if (*node)
    {
      dest = *node;
      (*node) = dest->next;
      g_hash_node_destroy (dest);
      nnodes--;

      RESIZE();

      return true;
    }

    return false;
  }

  void steal_all()
  {
    if (!nodes)
      return;

    guint i;

    for (i = 0; i < size; i++)
    {
      g_hash_nodes_destroy (nodes[i]);
      nodes[i] = NULL;
    }

    nnodes = 0;

    RESIZE();
  }

  guint foreach_remove(TMSCHRFunc   func, gpointer  user_data)
  {
    assert(func != NULL);

    return foreach_remove_or_steal(func, user_data/*, TRUE*/);
  }

  guint foreach_steal(TMSCHRFunc func, gpointer  user_data)
  {
    assert(func != 0);

    return foreach_remove_or_steal(func, user_data/*, FALSE*/);
  }

  guint foreach_remove_or_steal(TMSCHRFunc   func, gpointer    user_data/*, gboolean    notify*/)
  {
    if (!nodes)
      return 0;

    TMSCdirectHashNode *node, *prev;
    guint deleted = 0;

    for (guint i = 0; i < size; i++)
    {
restart:

      prev = NULL;

      for (node = nodes[i]; node; prev = node, node = node->next)
      {
        if ((* func) ((gpointer)node->key, (gpointer)node->value, user_data))
        {
          deleted += 1;

          nnodes -= 1;

          if (prev)
          {
            prev->next = node->next;
            g_hash_node_destroy (node);
            node = prev;
          }
          else
          {
            nodes[i] = node->next;
            g_hash_node_destroy (node);
            goto restart;
          }
        }
      }
    }

    RESIZE();

    return deleted;
  }

  void foreach_simple(TMSCHFunc    func, gpointer    user_data)
  {
    if (!nodes)
      return;

    TMSCdirectHashNode *node;

    assert(func != 0);

    for (guint i = 0; i < size; i++)
      for (node = nodes[i]; node; node = node->next)
        (* func) ((gpointer)node->key, (gpointer)node->value, user_data);
  }

  gpointer find(TMSCHRFunc      predicate, gpointer     user_data)
  {
    if (!nodes)
      return 0;

    TMSCdirectHashNode *node;

    assert(predicate != 0);

    for (guint i = 0; i < size; i++)
      for (node = nodes[i]; node; node = node->next)
        if (predicate ((gpointer)node->key, (gpointer)node->value, user_data))
          return node->value;
    return NULL;
  }

  guint get_size()
  {
    return nnodes;
  }

  void resize()
  {
    TMSCdirectHashNode **new_nodes;
    TMSCdirectHashNode *node;
    TMSCdirectHashNode *next;
    guint hash_val;
    guint new_size;

    new_size = g_spaced_primes_closest(nnodes * HASH_TABLE_RESIZE_MULTIPLIER_BOUND);
    new_size = HASH_TABLE_CLAMP (new_size, HASH_TABLE_MIN_SIZE, HASH_TABLE_MAX_SIZE);

    if (new_size == size) // we have no new primes
      return;

    new_nodes = (TMSCdirectHashNode**)calloc(new_size, sizeof(TMSCdirectHashNode*));

    for (guint i = 0; i < size; i++)
      for (node = nodes[i]; node; node = next)
      {
        next = node->next;

        hash_val = node->key_hash % new_size;

        node->next = new_nodes[hash_val];
        new_nodes[hash_val] = node;
      }

      free(nodes);
      nodes = new_nodes;
      size = new_size;
  }

  void g_hash_node_destroy(TMSCdirectHashNode *hash_node)
  {
    delete hash_node;
  }

  void g_hash_nodes_destroy (TMSCdirectHashNode *hash_node)
  {
    while (hash_node)
    {
      TMSCdirectHashNode *next = hash_node->next;
      delete hash_node;
      hash_node = next;
    }
  }
private:
  gpchar           name_;
  guint            size;
  guint            nnodes;
  TMSCdirectHashNode      **nodes;
};

//////////////////////////////////////////////////////////////////////////
class LOCAL_API TMSCPIDLIDHashNode
{
public:
  TMSCPIDLIDHashNode(guint32 key1, guint32 key2, void* value, guint key_hash):
    key1(key1), key2(key2), value(value), key_hash(key_hash), next(0) {}

  guint32   key1;
  guint32   key2;
  void*   value;
  TMSCPIDLIDHashNode *next;
  guint      key_hash;
};

class LOCAL_API TMSCPIDLIDHashTable
{
private:
  TMSCPIDLIDHashTable(const TMSCPIDLIDHashTable&) {}
  TMSCPIDLIDHashTable& operator=(const TMSCPIDLIDHashTable&) { return *this; }
public:
  TMSCPIDLIDHashTable(gconstpchar name = 0): name_(0)
  {
    size               = HASH_TABLE_MIN_SIZE;
    nnodes             = 0;
    nodes              = (TMSCPIDLIDHashNode**)calloc(size, sizeof(TMSCPIDLIDHashNode*));
    if (name != 0) {
      size_t l = strlen(name);
      name_ = (gpchar)malloc(l + 1);
      memmove(name_, name, l);
      name_[l] = 0;
    }
  }

  /*virtual*/ ~TMSCPIDLIDHashTable()
  {
    remove_all();
    if (nodes)
      free(nodes);
    if (name_ != 0) {
      free(name_);
      name_ = 0;
    }
  }

  void RESIZE()
  {
    if ((size >= HASH_TABLE_RESIZE_UPPER_BOUND * nnodes &&
      size > HASH_TABLE_MIN_SIZE) ||
      (size <= HASH_TABLE_RESIZE_LOWER_BOUND * nnodes &&
      size < HASH_TABLE_MAX_SIZE))
      resize();
  }

  TMSCPIDLIDHashNode** lookup_node (guint32 key1, guint32 key2, guint *hash_return)
  {
    TMSCPIDLIDHashNode **node;
    guint hash_value;

    hash_value = key1 + key2;
    node = &nodes[hash_value % size];

    if (hash_return)
      *hash_return = hash_value;

    while (*node && (((*node)->key1 != key1) || ((*node)->key2 != key2)))
      node = &(*node)->next;

    return node;
  }

  gsize_t nodes_in_place(guint32 key1, guint32 key2)
  {
    TMSCPIDLIDHashNode **node;
    guint hash_value = key1 + key2;
    gsize_t node_count = 0;

    node = &nodes[hash_value % size];

    while (*node) {
      node = &(*node)->next;
    }

    return node_count;
  }

  void* lookup(guint32 key1, guint32 key2)
  {
    if (!nodes)
      return 0;

    TMSCPIDLIDHashNode *node;

    node = *lookup_node(key1, key2, 0);

    return node ? node->value : 0;
  }

  void insert(guint32 key1, guint32 key2, void* value)
  {
    if (!nodes)
      resize();

    TMSCPIDLIDHashNode **node;
    guint key_hash;

    node = lookup_node(key1, key2, &key_hash);

    if (*node) {
      /* do not reset node->key in this place, keeping
      * the old key is the intended behavior.
      * replace() can be used instead.
      */

  //     (*node)->key = key;
      (*node)->value = value;
    } else {
      gsize_t nip = nodes_in_place(key1, key2);
      if (nip > 16)
        log_hash_table_insert_warning("TMSCPIDLIDHashTable", name_, "insert", nip);

      *node = new TMSCPIDLIDHashNode(key1, key2, value, key_hash);

      nnodes++;
      RESIZE();
    }
  }

  gboolean insert_if_none(guint32 key1, guint32 key2, void* value)
  {
    if (!nodes)
      resize();

    TMSCPIDLIDHashNode **node;
    guint key_hash;

    node = lookup_node(key1, key2, &key_hash);

    if (*node) {
      /* do not reset node->key in this place, keeping
      * the old key is the intended behavior.
      * replace() can be used instead.
      */
      return false;
    } else {
      gsize_t nip = nodes_in_place(key1, key2);
      if (nip > 16)
        log_hash_table_insert_warning("TMSCPIDLIDHashTable", name_, "insert_if_none", nip);

      *node = new TMSCPIDLIDHashNode(key1, key2, value, key_hash);

      nnodes++;
      RESIZE();
      return true;
    }
  }

  gboolean remove(guint32 key1, guint32 key2)
  {
    if (!nodes)
      return false;

    TMSCPIDLIDHashNode **node, *dest;

    node = lookup_node(key1, key2, NULL);
    if (*node)
    {
      dest = *node;
      (*node) = dest->next;
      g_hash_node_destroy (dest);
      nnodes--;

      RESIZE();

      return true;
    }

    return false;
  }

  void remove_all()
  {
    if (!nodes)
      return;

    guint i;

    for (i = 0; i < size; i++)
    {
      g_hash_nodes_destroy (nodes[i]);
      nodes[i] = NULL;
    }
    nnodes = 0;

    RESIZE();
  }

  guint get_size()
  {
    return nnodes;
  }

  void resize()
  {
    TMSCPIDLIDHashNode **new_nodes;
    TMSCPIDLIDHashNode *node;
    TMSCPIDLIDHashNode *next;
    guint hash_val;
    guint new_size;

    new_size = g_spaced_primes_closest(nnodes * HASH_TABLE_RESIZE_MULTIPLIER_BOUND);
    new_size = HASH_TABLE_CLAMP (new_size, HASH_TABLE_MIN_SIZE, HASH_TABLE_MAX_SIZE);

    if (new_size == size) // we have no new primes
      return;

    new_nodes = (TMSCPIDLIDHashNode**)calloc(new_size, sizeof(TMSCPIDLIDHashNode*));

    for (guint i = 0; i < size; i++)
      for (node = nodes[i]; node; node = next)
      {
        next = node->next;

        hash_val = node->key_hash % new_size;

        node->next = new_nodes[hash_val];
        new_nodes[hash_val] = node;
      }

      free(nodes);
      nodes = new_nodes;
      size = new_size;
  }

  void g_hash_node_destroy(TMSCPIDLIDHashNode *hash_node)
  {
    delete hash_node;
  }

  void g_hash_nodes_destroy(TMSCPIDLIDHashNode *hash_node)
  {
    while (hash_node)
    {
      TMSCPIDLIDHashNode *next = hash_node->next;
      delete hash_node;
      hash_node = next;
    }
  }

private:
  gpchar           name_;
  guint            size;
  guint            nnodes;
  TMSCPIDLIDHashNode      **nodes;
};

#endif

