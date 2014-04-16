/*
   This file is part of raveloxmidi.

   Copyright (C) 2014 Dave Kelly

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA 
*/

#ifndef NET_CONNECTION_H
#define NET_CONNECTION_H

#include "rtp_packet.h"
#include "midi_journal.h"

#define MAX_CTX 10

typedef struct net_ctx_t {
	uint8_t		used;
	uint32_t	ssrc;
	uint32_t	send_ssrc;
	uint32_t	initiator;
	uint32_t	seq;
	uint16_t	port;
	time_t		start;
	char * 		ip_address;
	journal_t	*journal;
} net_ctx_t;

void net_ctx_reset( net_ctx_t *ctx );
void debug_net_ctx_dump( net_ctx_t *ctx );
void net_ctx_init( void );
void net_ctx_destroy( void );
net_ctx_t * net_ctx_find_by_id( uint8_t id );
net_ctx_t * net_ctx_find_by_ssrc( uint32_t ssrc);
net_ctx_t * net_ctx_register( uint32_t ssrc, uint32_t initiator, char *ip_address, uint16_t port );
void net_ctx_add_journal_note( uint8_t ctx_id , char channel, char note, char velocity );
void debug_ctx_journal_dump( uint8_t ctx_id );
void net_ctx_journal_pack( uint8_t ctx_id, char **journal_buffer, size_t *journal_buffer_size);
void net_ctx_journal_reset( uint8_t ctx_id );
void net_ctx_update_rtp_fields( uint8_t ctx_id, rtp_packet_t *rtp_packet);
void net_ctx_send( uint8_t ctx_id, int send_socket, unsigned char *buffer, size_t buffer_len );

#endif