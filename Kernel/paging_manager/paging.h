#ifndef _PAGING_H
#define _PAGING_H

  #include "pagemap_list/pagemap_list.h"

  void map_process(void * pageAddr);
  void map_physical(void * logic, void * physical);
  void map_physical_reload(void * logic, void * physical);
  void map_pagemap_list(pagemap_list_t pm_list);
  void * get_logical_userland_page();
  void * get_logical_userland_stack_page();
  void * translate_addr_page(void * addr, void * page);
  void * get_logical_userland_heap_base_page();

#endif
