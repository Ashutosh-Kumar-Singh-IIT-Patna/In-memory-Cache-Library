# In-memory Cache Library

## Overview
This in-memory caching library is designed for general use, providing efficient data storage and retrieval with support for multiple standard eviction policies. The library is extendable, allowing users to add custom eviction policies as per their requirements. Additionally, it offers thread safety to ensure proper functioning in concurrent environments.

## Key Features

### Multiple Standard Eviction Policies
- **FIFO (First In, First Out)**: Evicts the oldest entry in the cache first.
- **LRU (Least Recently Used)**: Evicts the least recently accessed entry.
- **LIFO (Last In, First Out)**: Evicts the most recently added entry first.

### Custom Eviction Policies
- Allows users to define and integrate their own eviction policies tailored to specific use cases.

### Thread Safety
- Ensures that the cache operations are safe to use in multi-threaded environments, preventing data races and ensuring consistency.


### https://replit.com/@Ashutosh-Kumar9/In-memory-Cache-Library?v=1

### https://onlinegdb.com/GZ8kNmDhV
