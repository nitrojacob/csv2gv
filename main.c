/**
 * Program to convert a Tree representation in CSV file to a graphviz tree structure
 *
 * Author : Jacob Mathew
 *
 * Conventions
 * Lines are numbered from 1 onwards. (Variable i in main())
 * Columns are also numbered 1 onwards. (Variable j in main())
 *
 * Procedure
 * Create CSV from XLS/ODS file. Ensure there are no spaces in the file. If there are any convert them to _ character
 * Run this executable
 * Open the optput file using graphviz and generate the Tree diagram
 */
#include <stdio.h>
#include <string.h>

#define INPUT                 "./sampleTree.csv"
#define OUTPUT                "output.gv"
#define MAX_TREE_DEPTH        10
#define MAX_NAME_LENGTH       256
#define MAX_LINE_LENGTH       4096

#define NODE_LABEL_OFFSET     1


typedef struct{
  char branchLabel[MAX_NAME_LENGTH];
  char nodeLabel[MAX_NAME_LENGTH];
}graphNode;

/**
 * This function finds the next cursor posiontion that is a ,[comma] character
 */
int go_till_comma(char buffer[], int cursor)
{
  while(buffer[cursor]!=',' && buffer[cursor]!= '\0')
    cursor++;
  return cursor;
}

/**
 * Returns the column of buffer specified by column in the array output
 *
 * @arg buffer    [IN]  A full line of comma separated value
 *      output    [OUT] The text present in specified column
 *      column    [IN]  The column whose text needs to be read to output
 */
void csv_getColumn(char buffer[],char output[],int column)
{
  int i,cursor=0;
  int start;
  for(i=1;i<column;i++){
    cursor = go_till_comma(buffer, cursor);
    cursor++;
  }
  start = cursor;
  cursor = go_till_comma(buffer,cursor);
  strncpy(output,&buffer[start],cursor-start);
  output[cursor-start]='\0';
}

/**
 * Parses a single line of the .csv and returns the node depth and node & branch labels to be applied
 *
 * @arg buffer      [IN]  one full line of csv that is to be processed
 *      maxDepth    [IN]  max depth of the tree
 *      p_currNode  [OUT] Structure containing the current nodes label and incoming branch label
 */
int csv_parseLine(char buffer[], int maxDepth, graphNode* p_currNode)
{
  int j;

  /* Find the branch name */
  for(j=1; j<=maxDepth; j++)
  {
    csv_getColumn(buffer, p_currNode->branchLabel, j);
    if(strlen(p_currNode->branchLabel) != 0)
      break;
  }
  csv_getColumn(buffer, p_currNode->nodeLabel, maxDepth + NODE_LABEL_OFFSET);
  return j;
}

int main()
{
  int i,j;
  char buffer[MAX_LINE_LENGTH];
  graphNode currNode;
  int parents_row[MAX_TREE_DEPTH]={0};
  FILE *p_in, *p_out;

  p_in = fopen(INPUT,"r");
  p_out =  fopen(OUTPUT, "w");

  /* Header */
  fprintf(p_out,"graph forest{\n  node [shape = point];\n  rankdir=LR\n");

  /* Read each line */
  for (i=1;EOF != fscanf(p_in,"%s",buffer);i++)
  {

    j = csv_parseLine(buffer, MAX_TREE_DEPTH, &currNode);
    /* Create a node */
    if(currNode.nodeLabel[0]!='\0')
      fprintf(p_out,"  n_%d_%d [label = \"%s\" shape = oval];\n",i,j,currNode.nodeLabel);

    /* Mark the branch from newly created node to its parent */
    if(currNode.branchLabel[0]!='\0')
      fprintf(p_out,"  n_%d_%d -- n_%d_%d [label = \"%s\" fontcolor = black];\n",parents_row[j],j-1,i,j,currNode.branchLabel);
    else{
      printf("ERROR: Bad branch label for row: %d, column %d\n", i,j);
    }
    /* As we have found a new element in column j, the level j+1 can no longer have the old domain as the parent */
    parents_row[j+1]=i;
    printf("DEBUG: %d,%d,%s\n",i,j,currNode.branchLabel);
  }

  /* Footer */
  fprintf(p_out,"}\n");

  fclose(p_in);
  fclose(p_out);
  return 0;
}
