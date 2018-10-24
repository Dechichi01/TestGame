#pragma once

#define ENSURE ensure
#define ENSURE_MSG ensureMsgf
#define VERIFY verify
#define CHECK check

#define LogDebug(x, ...) UE_LOG(LogTemp, Log, TEXT(x), ##__VA_ARGS__)
#define LogWarning(x, ...) UE_LOG(LogWarning, Log, TEXT(x), ##__VA_ARGS__)