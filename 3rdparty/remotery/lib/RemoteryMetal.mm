
#include <Foundation/NSThread.h>
#include <Foundation/NSDictionary.h>
#include <Foundation/NSString.h>

#import <Metal/Metal.h>


// Store command buffer in thread-local so that each thread can point to its own
void SetCommandBuffer(id command_buffer)
{
    NSMutableDictionary* thread_data = [[NSThread currentThread] threadDictionary];
    thread_data[@"rmtMTLCommandBuffer"] = command_buffer;
}
id GetCommandBuffer()
{
    NSMutableDictionary* thread_data = [[NSThread currentThread] threadDictionary];
    return thread_data[@"rmtMTLCommandBuffer"];
}


void _rmt_BindMetal(id command_buffer)
{
    SetCommandBuffer(command_buffer);
}


void _rmt_UnbindMetal()
{
    SetCommandBuffer(0);
}


// Needs to be in the same lib for this to work
unsigned long long rmtMetal_usGetTime();


static void SetTimestamp(void* data)
{
    *((unsigned long long*)data) = rmtMetal_usGetTime();
}


void rmtMetal_MeasureCommandBuffer(unsigned long long* out_start, unsigned long long* out_end, unsigned int* out_ready)
{
    id command_buffer = GetCommandBuffer();
    [command_buffer addScheduledHandler:^(id <MTLCommandBuffer>){ SetTimestamp(out_start); }];
    [command_buffer addCompletedHandler:^(id <MTLCommandBuffer>){ SetTimestamp(out_end); *out_ready = 1; }];
}
