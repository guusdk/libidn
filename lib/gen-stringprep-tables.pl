#! /usr/bin/perl -w

# Copyright (C) 2002, 2003 Simon Josefsson

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

# I consider the output of this program to be unrestricted.  Use it as
# you will.

use strict;

my ($tab) = 59;
my ($intable) = 0;
my ($tablename);
my ($varname);
my ($starheader, $header);
my ($profile) = "rfc3454";
my ($filename) = "$profile.c";
my ($line, $start, $end, @map);

open(FH, ">$filename") or die "cannot open $filename for writing";

print FH "#include \"stringprep.h\"\n";

while(<>) {
    s/^   (.*)/$1/g; # for rfc
    $line = $_;

    die "already in table" if $intable && m,^----- Start Table (.*) -----,;
    die "not in table" if !$intable && m,^----- End Table (.*) -----,;

    if ($intable && m,^----- End Table (.*) -----,) {
	die "table error" unless $1 eq $tablename ||
	    ($1 eq "C.1.2" && $tablename eq "C.1.1"); # Typo in draft
	$intable = 0;
	print FH "  { 0 },\n";
	print FH "};\n\n";
    }

    if (m,^[A-Z],) {
	$header = $line;
    } elsif (!m,^[ -],) {
	$header .= $line;
    }

    next unless ($intable || m,^----- Start Table (.*) -----,);

    if ($intable) {
	$_ = $line;
	chop $line;

	next if m,^$,;
	next if m,^Hoffman & Blanchet          Standards Track                    \[Page [0-9]+\]$,;
	next if m,^$,;
	next if m,RFC 3454        Preparation of Internationalized Strings   December 2002,;

	die "regexp failed on line: $line" unless
	    m,^([0-9A-F]+)(-([0-9A-F]+))?(; ([0-9A-F]+)( ([0-9A-F]+))?( ([0-9A-F]+))?( ([0-9A-F]+))?;)?,;

	die "too many mapping targets on line: $line" if $12;

	$start = $1;
	$end = $3;
	$map[0] = $5;
	$map[1] = $7;
	$map[2] = $9;
	$map[3] = $11;

	die "tables tried to map a range" if $end && $map[0];

	if ($map[3]) {
	    printf FH "  { 0x%06s, 0, { 0x%06s,%*s/* %s */\n                   0x%06s, 0x%06s, 0x%06s }},\n",
	    $start, $map[0], $tab-length($line)-13, " ", $line,
	    $map[1], $map[2], $map[3];
	} elsif ($map[2]) {
	    printf FH "  { 0x%06s, 0, { 0x%06s,%*s/* %s */\n                   0x%06s, 0x%06s }},\n",
	    $start, $map[0], $tab-length($line)-14, " ", $line,
	    $map[1], $map[2];
	} elsif ($map[1]) {
	    printf FH "  { 0x%06s, 0, { 0x%06s,%*s/* %s */\n                   0x%06s }},\n",
	    $start, $map[0], $tab-length($line)-14, " ", $line,
	    $map[1];
	} elsif ($map[0]) {
	    printf FH "  { 0x%06s, 0, { 0x%06s }},%*s/* %s */\n",
	    $start, $map[0], $tab-length($line)-17, " ",  $line;
	} elsif ($end) {
	    printf FH "  { 0x%06s, 0x%06s },%*s/* %s */\n",
	    $start, $end, $tab-length($line)-11, " ",  $line;
	} else {
	    printf FH "  { 0x%06s           },%*s/* %s */\n",
	    $start, $tab-length($line)-11, " ",  $line;
	}
    } else {
	$intable = 1 if !$intable;
	$tablename = $1;

	($varname = $tablename) =~ tr/./_/;
	$header =~ s/\n/\n * /s;

	print FH "\n/*\n * $header */\n\n";
	print FH "Stringprep_table_element stringprep_${profile}_${varname}\[\] = {\n";
    }
}

close FH or die "cannot close $filename";
