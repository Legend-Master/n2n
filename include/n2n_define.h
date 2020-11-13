/**
 * (C) 2007-20 - ntop.org and contributors
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not see see <http://www.gnu.org/licenses/>
 *
 */

/* N2N packet header indicators. */
#define MSG_TYPE_REGISTER               1
#define MSG_TYPE_DEREGISTER             2
#define MSG_TYPE_PACKET                 3
#define MSG_TYPE_REGISTER_ACK           4
#define MSG_TYPE_REGISTER_SUPER         5
#define MSG_TYPE_REGISTER_SUPER_ACK     6
#define MSG_TYPE_REGISTER_SUPER_NAK     7
#define MSG_TYPE_FEDERATION             8
#define MSG_TYPE_PEER_INFO              9
#define MSG_TYPE_QUERY_PEER            10
#define MSG_TYPE_MAX_TYPE	       10

/* Max available space to add supernodes' informations (sockets and MACs) in REGISTER_SUPER_ACK
 * Field sizes of REGISTER_SUPER_ACK as used in encode/decode fucntions in src/wire.c
 * REVISIT: replace 255 by DEFAULT_MTU as soon as header encryption allows for longer packets to be encrypted. */
#define REG_SUPER_ACK_PAYLOAD_SPACE \
	(255-(1+1+2+sizeof(n2n_common_t)+sizeof(n2n_cookie_t)+sizeof(n2n_mac_t)+1+2+4+1+sizeof(n2n_sock_t)+1)) \

/* Space needed to store socket and MAC address of a supernode */
#define REG_SUPER_ACK_PAYLOAD_ENTRY_SIZE		(sizeof(n2n_sock_t)+sizeof(n2n_mac_t))

#define PURGE_REGISTRATION_FREQUENCY   30
#define RE_REG_AND_PURGE_FREQUENCY     10
#define REGISTRATION_TIMEOUT           60

#define SOCKET_TIMEOUT_INTERVAL_SECS    10
#define REGISTER_SUPER_INTERVAL_DFL     20 /* sec, usually UDP NAT entries in a firewall expire after 30 seconds */
#define SWEEP_TIME                      30 /* sec, indicates the value after which we have to sort the hash list of supernodes in edges
                                            * and when we send out packets to query selection-relevant informations from supernodes. */

/* Timeouts used in re_register_and_purge_supernodes. LAST_SEEN_SN_ACTIVE and LAST_SEEN_SN_INACTIVE
 * values should be at least 3*SOCKET_TIMEOUT_INTERVAL_SECS apart. */
#define LAST_SEEN_SN_ACTIVE      20 /* sec, indicates supernodes that are proven to be active */
#define LAST_SEEN_SN_INACTIVE    90 /* sec, indicates supernodes that are proven to be inactive: they will be purged */
#define LAST_SEEN_SN_NEW         (LAST_SEEN_SN_INACTIVE - LAST_SEEN_SN_ACTIVE)/2 /* sec, indicates supernodes with unsure status, must be tested to check if they are active */


#define IFACE_UPDATE_INTERVAL           (30) /* sec. How long it usually takes to get an IP lease. */
#define TRANSOP_TICK_INTERVAL           (10) /* sec */

#define SORT_COMMUNITIES_INTERVAL      90 /* sec. until supernode sorts communities' hash list again */

#define ETH_FRAMESIZE 14
#define IP4_SRCOFFSET 12
#define IP4_DSTOFFSET 16
#define IP4_MIN_SIZE  20
#define UDP_SIZE      8

/* parameters for replay protection */
#define TIME_STAMP_FRAME	0x0000001000000000LL /* clocks of different computers are allowed +/- 16 seconds to be off */
#define TIME_STAMP_JITTER	0x0000000027100000LL /* we allow a packet to arrive 160 ms (== 0x27100 us) before another
                                                      * set to 0x0000000000000000LL if increasing (or equal) time stamps allowed only */
#define TIME_STAMP_ALLOW_JITTER                    1 /* constant for allowing or... */
#define TIME_STAMP_NO_JITTER                       0 /* not allowing jitter to be considered */

/* N2N compression indicators. */
/* Compression is disabled by default for outgoing packets if no cli
 * option is given. All edges are built with decompression support so
 * they are able to understand each other (this applies to lzo only). */
#define N2N_COMPRESSION_ID_INVALID	0
#define N2N_COMPRESSION_ID_NONE		1	/* default, see edge_init_conf_defaults(...) in edge_utils.c */
#define N2N_COMPRESSION_ID_LZO		2	/* set if '-z1' or '-z' cli option is present, see setOption(...) in edge.c */
#define N2N_COMPRESSION_ID_ZSTD		3	/* set if '-z2' cli option is present, available only if compiled with zstd lib */
#define ZSTD_COMPRESSION_LEVEL		7	/* 1 (faster) ... 22 (more compression) */

/* Federation name and indicators */
#define FEDERATION_NAME "*Federation"
enum federation{IS_NO_FEDERATION = 0,IS_FEDERATION = 1};

/* (un)purgeable community indicator (supernode) */
#define COMMUNITY_UNPURGEABLE		0
#define COMMUNITY_PURGEABLE		1

/* (un)purgeable supernode indicator */
enum sn_purge{SN_PURGEABLE = 0, SN_UNPURGEABLE = 1};

/* Header encryption indicators */
#define HEADER_ENCRYPTION_UNKNOWN       0
#define HEADER_ENCRYPTION_NONE          1
#define HEADER_ENCRYPTION_ENABLED       2

#define DEFAULT_MTU   1290

#define HASH_ADD_PEER(head,add)				\
  HASH_ADD(hh,head,mac_addr,sizeof(n2n_mac_t),add)
#define HASH_FIND_PEER(head,mac,out)		\
  HASH_FIND(hh,head,mac,sizeof(n2n_mac_t),out)
#define N2N_EDGE_SN_HOST_SIZE   48
#define N2N_EDGE_NUM_SUPERNODES 2
#define N2N_EDGE_SUP_ATTEMPTS   3       /* Number of failed attmpts before moving on to next supernode. */
#define N2N_PATHNAME_MAXLEN     256
#define N2N_EDGE_MGMT_PORT      5644
#define N2N_SN_MGMT_PORT        5645

/* flag used in add_sn_to_list_by_mac_or_sock */
enum skip_add{SN_ADD = 0, SN_ADD_SKIP = 1, SN_ADD_ADDED = 2};

#define N2N_NETMASK_STR_SIZE    16 /* dotted decimal 12 numbers + 3 dots */
#define N2N_MACNAMSIZ           18 /* AA:BB:CC:DD:EE:FF + NULL*/
#define N2N_IF_MODE_SIZE        16 /* static | dhcp */

#define N2N_EDGE_DEFAULT_DEV_NAME  "edge0"
#define N2N_EDGE_DEFAULT_NETMASK   "255.255.255.0"  /* default netmask for edge ip address... */
#define N2N_EDGE_DEFAULT_CIDR_NM   24               /* ... also in cidr format                */

#define N2N_SN_LPORT_DEFAULT 7654
#define N2N_SN_PKTBUF_SIZE   2048


/* The way TUNTAP allocated IP. */
#define TUNTAP_IP_MODE_SN_ASSIGN 0
#define TUNTAP_IP_MODE_STATIC 1
#define TUNTAP_IP_MODE_DHCP 2

/* Default network segment of the auto ip address service provided by sn. */
#define N2N_SN_MIN_AUTO_IP_NET_DEFAULT "10.128.0.0"
#define N2N_SN_MAX_AUTO_IP_NET_DEFAULT "10.255.255.0"
#define N2N_SN_AUTO_IP_NET_BIT_DEFAULT 24

/* ************************************** */

#define SUPERNODE_IP    "127.0.0.1"
#define SUPERNODE_PORT  1234

/* ************************************** */

#define N2N_PKT_VERSION                 3
#define N2N_DEFAULT_TTL                 2       /* can be forwarded twice at most */
#define N2N_COMMUNITY_SIZE              16
#define N2N_MAC_SIZE                    6
#define N2N_COOKIE_SIZE                 4
#define N2N_DESC_SIZE                   16
#define N2N_PKT_BUF_SIZE                2048
#define N2N_SOCKBUF_SIZE                64      /* string representation of INET or INET6 sockets */

#define N2N_MULTICAST_PORT              1968
#define N2N_MULTICAST_GROUP             "224.0.0.68"

#ifdef WIN32
#define N2N_IFNAMSIZ            64
#else
#define N2N_IFNAMSIZ            16 /* 15 chars * NULL */
#endif

#define SN_SELECTION_CRITERION_DATA_TYPE   uint32_t
#define SN_SELECTION_CRITERION_BUF_SIZE   14

#define N2N_TRANSFORM_ID_USER_START     64
#define N2N_TRANSFORM_ID_MAX            65535

#ifndef max
#define max(a, b) ((a < b) ? b : a)
#endif

#ifndef min
#define min(a, b) ((a > b) ? b : a)
#endif
