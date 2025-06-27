# ft_ping

A custom implementation of the `ping` utility written in C, designed to test network connectivity using ICMP Echo Request packets.

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Command Line Options](#command-line-options)
- [Project Structure](#project-structure)
- [Technical Details](#technical-details)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)

## 🔍 Overview

`ft_ping` is a network diagnostic tool that sends ICMP Echo Request packets to network hosts and measures the round-trip time for messages sent from the originating host to a destination computer. This implementation replicates the core functionality of the standard Unix `ping` command.

## ✨ Features

- **ICMP Echo Request/Reply**: Sends and receives ICMP packets for network connectivity testing
- **Domain Name Resolution**: Supports both IP addresses and domain names
- **Round-Trip Time Calculation**: Measures and displays packet travel time
- **Packet Loss Detection**: Tracks transmitted vs received packets
- **Statistical Analysis**: Provides min/avg/max/mdev statistics
- **Verbose Mode**: Detailed packet information display
- **Signal Handling**: Graceful termination with Ctrl+C
- **Raw Socket Implementation**: Low-level network programming using raw sockets

## 🛠 Requirements

- **Operating System**: Linux/macOS (Unix-like systems)
- **Compiler**: GCC or Clang with C99 support
- **Privileges**: Root/sudo access (required for raw sockets)
- **Dependencies**: Standard C library, POSIX compliant system

### System Libraries Used

- `netinet/ip.h` - IP header structures
- `netinet/ip_icmp.h` - ICMP header structures
- `sys/socket.h` - Socket programming
- `arpa/inet.h` - Internet address manipulation
- `netdb.h` - Network database operations

## 🚀 Installation

1. **Clone the repository:**
   ```bash
   git clone <repository-url>
   cd ft_ping
   ```

2. **Build the project:**
   ```bash
   make
   ```

3. **Clean build files (optional):**
   ```bash
   make clean    # Remove object files
   make fclean   # Remove all generated files
   make re       # Rebuild from scratch
   ```

## 📖 Usage

**Basic syntax:**
```bash
sudo ./ft_ping [FLAG] [IP/DOMAIN]
```

**Note:** Root privileges are required due to raw socket usage.

## 🎛 Command Line Options

| Flag | Description |
|------|-------------|
| `-v` | **Verbose mode** - Display detailed packet information including packet ID |
| `-?` | **Help** - Show usage information and exit |

### Input Formats

- **IP Address**: `xxx.xxx.xxx.xxx` (e.g., `192.168.1.1`)
- **Domain Name**: `www.example.com` (e.g., `google.com`)

## 📁 Project Structure

```
ft_ping/
├── Makefile              # Build configuration
├── README.md            # Project documentation
└── src/
    ├── ft_ping.h        # Header file with declarations
    ├── main.c           # Program entry point
    ├── packet.c         # Core packet handling logic
    ├── packet_utils.c   # Packet utility functions
    ├── packet_utils2.c  # Additional packet utilities
    ├── utils.c          # General utility functions
    ├── utils2.c         # Additional utilities
    ├── validation.c     # Input validation functions
    └── libft/          # Custom C library
```

## 🔧 Technical Details

### Core Components

- **Raw Socket Creation**: Uses `SOCK_RAW` with `IPPROTO_ICMP`
- **IP Header Construction**: Manual IP header creation with proper fields
- **ICMP Packet Format**: Echo Request (type 8) and Echo Reply (type 0)
- **Checksum Calculation**: RFC-compliant ICMP checksum computation
- **Timing Mechanisms**: High-precision timing using `gettimeofday()`

### Network Protocol Stack

- **Layer 3 (Network)**: IP and ICMP protocol implementation
- **Socket Options**: IP header inclusion and receive timeout configuration
- **Signal Handling**: SIGINT handler for graceful shutdown

### Key Data Structures

```c
typedef struct s_ping {
    char    *dest_ip;           // Destination IP/domain
    char    *ip_rep;            // Resolved IP address
    char    *packet;            // Packet buffer
    char    *buffer;            // Receive buffer
    float   *timings;           // RTT measurements
    int     transmitted_packets; // Packets sent
    int     recieved_packets;   // Packets received
    // ... additional fields
} t_ping;
```

## 💡 Examples

### Basic Usage

```bash
# Ping an IP address
sudo ./ft_ping 8.8.8.8

# Ping a domain name
sudo ./ft_ping google.com
```

### Verbose Mode

```bash
# Display detailed packet information
sudo ./ft_ping -v google.com
```

### Expected Output

```
PING google.com (172.217.16.142): 56 data bytes, id 0x1234 = 4660
64 bytes from 172.217.16.142: icmp_seq=1 ttl=55 time=12.345 ms
64 bytes from 172.217.16.142: icmp_seq=2 ttl=55 time=11.234 ms
^C
--- google.com ft_ping statistics ---
2 packets transmitted, 2 received, 0.0000% packet loss, time 1001 ms
rtt min/avg/max/mdev = 11.234/11.789/12.345/0.555 ms
```

## 🏗 Architecture

### Packet Flow

1. **Initialization**: Setup socket, resolve domain name
2. **Packet Construction**: Build IP and ICMP headers
3. **Transmission**: Send packet via raw socket
4. **Reception**: Receive reply with timeout
5. **Analysis**: Calculate RTT, update statistics
6. **Repeat**: Continue until interrupted

### Error Handling

- Domain resolution failures
- Socket creation errors
- Packet transmission failures
- Memory allocation errors
- Invalid command line arguments

## 🧪 Development

### Building from Source

The project uses a custom `libft` library and requires specific compilation flags:

```bash
# Compiler flags used
-Wall -Wextra -Werror

# Linking with libft
src/libft/libft.a
```

### Memory Management

- Dynamic allocation for packet buffers
- Proper cleanup on exit and error conditions
- Signal-safe memory handling

## 🐛 Troubleshooting

### Common Issues

1. **Permission Denied**: Ensure running with `sudo`
2. **Network Unreachable**: Check network connectivity
3. **Name Resolution Failed**: Verify domain name or DNS settings
4. **Socket Creation Failed**: Check system socket limits

### Debug Mode

Use the verbose flag (`-v`) for detailed packet analysis and debugging information.