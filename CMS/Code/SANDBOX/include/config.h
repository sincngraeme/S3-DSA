// config.h
/************************************************************//*
*   By Nigel Sinclair, Fergus Page
*   Contains global config settings for comport and data opps
*/ 
#pragma once

typedef struct hdrConfig {

    short sid;
    short rid;
    int audioCompType;      // 0: None  1: RLE  2: Huffman  3: Both
    int textCompType;       // 0: None  1: RLE  2: Huffman  3: Both
    
} hConfig;

typedef struct comConfig {
    int bitrate;
    int bitdepth;
    wchar_t comport[6];
} cConfig;

typedef struct config {
    hConfig hdr;
    cConfig com;
} Config;

extern config settings;