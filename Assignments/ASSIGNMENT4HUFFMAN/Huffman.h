/*************************************************************************
* Name:        huffman.h
* Author:      Marcus Geelnard
* Description: Huffman coder/decoder interface.
* Reentrant:   Yes
*-------------------------------------------------------------------------
* Copyright (c) 2003-2006 Marcus Geelnard
*
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would
*    be appreciated but is not required.
*
* 2. Altered source versions must be plainly marked as such, and must not
*    be misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any source
*    distribution.
*
* Marcus Geelnard
* marcus.geelnard at home.se
*************************************************************************/

#ifndef _huffman_h_
#define _huffman_h_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* _huffman_h_ */
   

    /* The maximum number of nodes in the Huffman tree is 2^(8+1)-1 = 511 */
#define MAX_TREE_NODES 511

typedef struct huff_encodenode_struct huff_encodenode_t;

struct huff_encodenode_struct {
    huff_encodenode_t* ChildA, * ChildB;
    int Count;
    int Symbol;
};
typedef struct huff_decodenode_struct huff_decodenode_t;

struct huff_decodenode_struct {
    huff_decodenode_t* ChildA, * ChildB;
    int Symbol;
};

    /*************************************************************************
    * Function prototypes (C wrappers for the Huff class)
    *************************************************************************/
    


    /*************************************************************************
    * Function prototypes
    *************************************************************************/

    class Huff{
    private:

        typedef struct {
            unsigned char* BytePtr;
            unsigned int  BitPos;
        } huff_bitstream_t;

        typedef struct {
            int Symbol;
            unsigned int Count;
            unsigned int Code;
            unsigned int Bits;
        } huff_sym_t;


        static void _Huffman_InitBitstream(huff_bitstream_t* stream, unsigned char* buf);
        static unsigned int _Huffman_ReadBit(huff_bitstream_t* stream);
        static unsigned int _Huffman_Read8Bits(huff_bitstream_t* stream);
        static void _Huffman_WriteBits(huff_bitstream_t* stream, unsigned int x, unsigned int bits);
        static void _Huffman_Hist(unsigned char* in, huff_sym_t* sym, unsigned int size);

        // tree funcitons
        static void _Huffman_StoreTree(huff_encodenode_t* node, huff_sym_t* sym,
            huff_bitstream_t* stream, unsigned int code, unsigned int bits);
        static void _Huffman_MakeTree(huff_sym_t* sym, huff_bitstream_t* stream);
        static huff_decodenode_t* _Huffman_RecoverTree(huff_decodenode_t* nodes,
            huff_bitstream_t* stream, unsigned int* nodenum);

    public:

        int Huffman_Compress(unsigned char* in, unsigned char* out, unsigned int insize);
        void Huffman_Uncompress(unsigned char* in, unsigned char* out, unsigned int insize, unsigned int outsize);
        /*int Huffman_Compress_C(unsigned char* in, unsigned char* out, unsigned int insize);
        void Huffman_Uncompress_C(unsigned char* in, unsigned char* out, unsigned int insize, unsigned int outsize);*/
    };


