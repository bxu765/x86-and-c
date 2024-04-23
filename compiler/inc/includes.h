/**
 * File              : code_generator.c
 * Author            : Alenkruth Krishnan Murali <<firstname>[at]virginia{dot}edu>
 *                   : Daniel George Graham, Professor, UVA.
 *                   : Tom Niemann (https://www.epaperpress.com/lexandyacc/index.html)
 * Date              : 05.04.2024
 * Last Modified Date: 05.04.2024
 * Last Modified By  : Alenkruth Krishnan Murali <<firstname>[at]virginia{dot}edu>
 */

/* Creating an enumerated type */
/* for the tokens types we support. Namely, Constant(Integer), Variable(Identifier) and Operations(Operator). */
typedef enum { typeCon, typeId, typeOpr } nodeEnum;

/* constants */
typedef struct {
    int value;                  /* value of constant */
} conNodeType;

/* identifiers */
typedef struct {
    int i;                      /* subscript to sym array */
} idNodeType;

/* operators */
typedef struct {
    int oper;                   /* operator */
    int nops;                   /* number of operands */
    struct nodeTypeTag *op[1];	/* operands, extended at runtime */
} oprNodeType;

/* Node in our AST */
typedef struct nodeTypeTag {
    nodeEnum type;              /* type of node */

    union {                     /* union because any node can be only one of the three types */   
        conNodeType con;        /* constants */
        idNodeType id;          /* identifiers */
        oprNodeType opr;        /* operators */
    };
} nodeType;

/* We implement variables as a sequence of 26 memeory spaces, each of 8 byte size. */
extern int sym[26]; /* These are our identifiers/variables */
