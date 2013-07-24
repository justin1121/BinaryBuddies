#pragma once

void * get_memory(int);
void * grow_memory(int, void *);
void * pregrow_memory(int, void *);
void release_memory(void *);
int start_memory(int);
void end_memory(void);
