#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h> // For isspace()
#include <stdarg.h>

#include <table.h>
#include <array_1d.h>

#define MAXSIZE 80000

/*
 * Implementation of a generic table for the "Datastructures and
 * algorithms" courses at the Department of Computing Science, Umea
 * University.
 *
 * Duplicates are handled by inspect and remove.
 *
 * Authors: Niclas Borlin (niclas@cs.umu.se)
 *          Adam Dahlgren Lindstrom (dali@cs.umu.se)
 *
 * Based on earlier code by: Johan Eliasson (johane@cs.umu.se).
 *
 * Version information:
 *   v1.0  2018-02-06: First public version.
 *   v1.1  2019-02-21: Second version without dlist/memfreehandler.
 *   v1.2  2019-03-04: Bugfix in table_remove.
 *   v1.3  2024-04-15: Added table_print_internal.
 *   v2.0  2024-05-10: Updated print_internal with improved encapsulation.
 */

// ===========INTERNAL DATA TYPES ============

struct table {
    array_1d *entries; // The table entries are stored in a directed list
    compare_function *key_cmp_func;
    kill_function key_kill_func;
    kill_function value_kill_func;
    int first_free_pos;
};

typedef struct table_entry {
    void *key;
    void *value;
} table_entry;

// ===========INTERNAL FUNCTION IMPLEMENTATIONS ============

/**
 * table_entry_create() - Allocate and populate a table entry.
 * @key: A pointer to a function to be used to compare keys.
 * @value: A pointer to a function (or NULL) to be called to
 *                 de-allocate memory for keys on remove/kill.
 *
 * Returns: A pointer to the newly created table entry.
 */
table_entry *table_entry_create(void *key, void *value)
{
    // Allocate space for a table entry. Use calloc as a defensive
    // measure to ensure that all pointers are initialized to NULL.
    table_entry *e = calloc(1, sizeof(*e));
    // Populate the entry.
    e->key = key;
    e->value = value;

    return e;
}

/**
 * table_entry_kill() - Return the memory allocated to a table entry.
 * @e: The table entry to deallocate.
 *
 * Returns: Nothing.
 */
void table_entry_kill(void *v)
{
    table_entry *e = v; // Convert the pointer (useful if debugging the code)

    // All we need to do is to deallocate the struct.
    free(e);
}

/**
 * table_empty() - Create an empty table.
 * @key_cmp_func: A pointer to a function to be used to compare keys.
 * @key_kill_func: A pointer to a function (or NULL) to be called to
 *                 de-allocate memory for keys on remove/kill.
 * @value_kill_func: A pointer to a function (or NULL) to be called to
 *                   de-allocate memory for values on remove/kill.
 *
 * Returns: Pointer to a new table.
 */
table *table_empty(compare_function *key_cmp_func,
                   kill_function key_kill_func,
                   kill_function value_kill_func)
{
    // Allocate memory for table
    table *t = malloc(sizeof(table));

    // Create list to hold the table entries
    t->entries = array_1d_create(0, MAXSIZE-1, NULL);
    t->first_free_pos = 0;

    // Store the key compare function and key/value kill functions.
    t->key_cmp_func = key_cmp_func;
    t->key_kill_func = key_kill_func;
    t->value_kill_func = value_kill_func;
    
    return t;
}

/**
 * table_is_empty() - Check if a table is empty.
 * @table: Table to check.
 *
 * Returns: True if table contains no key/value pairs, false otherwise.
 */
bool table_is_empty(const table *t)
{
    return t->first_free_pos == 0;
}

/**
 * table_insert() - Add a key/value pair to a table.
 * @table: Table to manipulate.
 * @key: A pointer to the key value.
 * @value: A pointer to the value value.
 *
 * Insert the key/value pair into the table. No test is performed to
 * check if key is a duplicate. table_lookup() will return the latest
 * added value for a duplicate key. table_remove() will remove all
 * duplicates for a given key.
 *
 * Returns: Nothing.
 */

void table_insert(table *t, void *key, void *value) {
    // Initiate index
    int i = 0;

    // Search for key matches
    while(array_1d_inspect_value(t->entries, i) != NULL)
    {
        table_entry *e = array_1d_inspect_value(t->entries, i);
    
        if(t->key_cmp_func(e->key, key) == 0)
        {
            // Free alloceated memory
            if (t->key_kill_func != NULL) 
            {
				t->key_kill_func(e->key);		
			}
            if (t->value_kill_func != NULL) 
            {
				t->value_kill_func(e->value);	
			}

            // Set pointer to new key and value
            e->key = key;
			e->value = value;
            return;      
        }
        
        i++;
    }

    // Increment first_free_pos
    t->first_free_pos++;	 
    if(t->first_free_pos > MAXSIZE)
    {
        return;
    }

     //create table entry
     table_entry *e = table_entry_create(key, value);
        
     // Set pointer to table entry in array, increment first_free_pos
     array_1d_set_value(t->entries, e, i);   
     
     
}

/**
 * table_lookup() - Look up a given key in a table.
 * @table: Table to inspect.
 * @key: Key to look up.
 *
 * Returns: The value corresponding to a given key, or NULL if the key
 * is not found in the table. If the table contains duplicate keys,
 * the value that was latest inserted will be returned.
 */
void *table_lookup(const table *t, const void *key)
{
    // Initiate index 
    int i = 0;

    // Search for key matches
    while(array_1d_inspect_value(t->entries, i) != NULL)
    {
        table_entry *e = array_1d_inspect_value(t->entries, i);
    
        if(t->key_cmp_func(e->key, key) == 0)
        {
            return e->value;      
        }
        i++;
    }

    //no matches found
    return NULL;
}

/**
 * table_choose_key() - Return an arbitrary key.
 * @t: Table to inspect.
 *
 * Return an arbitrary key stored in the table. Can be used together
 * with table_remove() to deconstruct the table. Undefined for an
 * empty table.
 *
 * Returns: An arbitrary key stored in the table.
 */
void *table_choose_key(const table *t)
{
    // Return top key value.
    table_entry *e = array_1d_inspect_value(t->entries, t->first_free_pos-1);
    return e->key;
}

/**
 * table_remove() - Remove a key/value pair in the table.
 * @table: Table to manipulate.
 * @key: Key for which to remove pair.
 *
 * Any matching duplicates will be removed. Will call any kill
 * functions set for keys/values. Does nothing if key is not found in
 * the table.
 *
 * Returns: Nothing.
 */
void table_remove(table *t, const void *key)
{
    // Initiate index
	int i = 0;	

    // Search for key match
	while (array_1d_inspect_value(t->entries, i) != NULL && i < MAXSIZE) 
    {	
        // Inspect table entry
		table_entry *e= array_1d_inspect_value(t->entries, i);
		
		// If key match is found, remove entry
		if ((t->key_cmp_func(e->key, key)) == 0) 
        {
			// Deallocate memory for key/value pair
			if (t->key_kill_func != NULL) 
            {
				t->key_kill_func(e->key);
			}
			if (t->value_kill_func != NULL) 
            {
				t->value_kill_func(e->value);
			}

			// Pointer to last entry in array
			table_entry *last_e = array_1d_inspect_value(t->entries, t->first_free_pos-1);
		
            // Move last entry to fill empty array slot
			e->key = last_e->key;
			e->value = last_e->value;
			
            // Deallocate memory for last array slot
			array_1d_set_value(t->entries, NULL, t->first_free_pos-1);
			table_entry_kill(last_e);
			
			// Decrement first_free_pos
			t->first_free_pos--;
            return;
        }
        i++;
    }
}   

/*
 * table_kill() - Destroy a table.
 * @table: Table to destroy.
 *
 * Return all dynamic memory used by the table and its elements. If a
 * kill_func was registered for keys and/or values at table creation,
 * it is called each element to kill any user-allocated memory
 * occupied by the element values.
 *
 * Returns: Nothing.
 */
void table_kill(table *t)
{
    // Initiate index
    int i = 0;	

	while (array_1d_inspect_value(t->entries, i) != NULL && i < MAXSIZE) 
    {
        table_entry *e = array_1d_inspect_value(t->entries, i);
		
		// Deallocate key/value
		if (t->key_kill_func != NULL) 
        {
				t->key_kill_func(e->key);
		}
		if (t->value_kill_func != NULL) 
        {
			t->value_kill_func(e->value);
		}

		// Free table entry
		free(e);
		i++;
	}
	// Destroy the rest of the table structure
	array_1d_kill(t->entries);
	free(t);
}

/**
 * table_print() - Print the given table.
 * @t: Table to print.
 * @print_func: Function called for each key/value pair in the table.
 *
 * Iterates over the key/value pairs in the table and prints them.
 * Will print all stored elements, including duplicates.
 *
 * Returns: Nothing.
 */
void table_print(const table *t, inspect_callback_pair print_func)
{
    // Initiate index
    int i = 0;

    // Iterate over entries and print
	while (array_1d_inspect_value(t->entries, i) != NULL && i < MAXSIZE) 
    {	
		table_entry *e = array_1d_inspect_value(t->entries, i);	
		print_func(e->key, e->value);

        i++;
	}
}

/**
 * table_print_internal() - Output the internal structure of the table.
 * @t: Table to print.
 * @key_print_func: Function called for each key in the table.
 * @value_print_func: Function called for each value in the table.
 * @desc: String with a description/state of the list.
 * @indent_level: Indentation level, 0 for outermost
 *
 * Iterates over the list and prints code that shows its' internal structure.
 *
 * Returns: Nothing.
 *

void table_print_internal(const table *t, inspect_callback key_print_func,
                          inspect_callback value_print_func, const char *desc,
                          int indent_level)
{
    static int graph_number = 0;
    graph_number++;
    int il = indent_level;

    if (indent_level == 0) {
        // If this is the outermost datatype, start a graph and set up defaults
        printf("digraph TABLE_%d {\n", graph_number);

        // Specify default shape and fontname
        il++;
        iprintf(il, "node [shape=rectangle fontname=\"Courier New\"]\n");
        iprintf(il, "ranksep=0.01\n");
        iprintf(il, "subgraph cluster_nullspace {\n");
        iprintf(il+1, "NULL\n");
        iprintf(il, "}\n");
    }

    if (desc != NULL) {
        // Escape the string before printout
        char *escaped = escape_chars(desc);
        // Optionally, splice the source file name
        char *spliced = insert_table_name(escaped);

        // Use different names on inner description nodes
        if (indent_level == 0) {
            iprintf(il, "description [label=\"%s\"]\n", spliced);
        } else {
            iprintf(il, "\tcluster_list_%d_description [label=\"%s\"]\n", graph_number, spliced);
        }
        // Return the memory used by the spliced and escaped strings
        free(spliced);
        free(escaped);
    }

    if (indent_level == 0) {
        // Use a single "pointer" edge as a starting point for the
        // outermost datatype
        iprintf(il, "t [label=\"%04lx\" xlabel=\"t\"]\n", PTR2ADDR(t));
        iprintf(il, "t -> m%04lx\n", PTR2ADDR(t));
    }

    if (indent_level == 0) {
        // Put the user nodes in userspace
        iprintf(il, "subgraph cluster_userspace { label=\"User space\"\n");
        il++;

        // Iterate over the list to print the payload nodes
        dlist_pos p = dlist_first(t->entries);
        while (!dlist_is_end(t->entries, p)) {
            print_key_value_nodes(il, dlist_inspect(t->entries, p), key_print_func,
                                  value_print_func);
            // Advance
            p = dlist_next(t->entries, p);
        }

        // Close the subgraph
        il--;
        iprintf(il, "}\n");
    }

    // Print the subgraph to surround the DList content
    iprintf(il, "subgraph cluster_table_%d { label=\"Table\"\n", graph_number);
    il++;

    // Output the head node
    print_head_node(il, t);

    // Output the edges from the head
    print_head_edge(il, t);

    if (t->entries) {
        // First, ask the dlist to output its internal structure.
        dlist_print_internal(t->entries, NULL, NULL, il);
    }

    // Close the subgraph
    il--;
    iprintf(il, "}\n");

    // Next, print each element stored in the list
    print_entries(il, t, key_print_func, value_print_func);

    if (indent_level == 0) {
        // Termination of graph
        printf("}\n");
    }
}*/
