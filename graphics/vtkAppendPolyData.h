/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkAppendPolyData.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


Copyright (c) 1993-1998 Ken Martin, Will Schroeder, Bill Lorensen.

This software is copyrighted by Ken Martin, Will Schroeder and Bill Lorensen.
The following terms apply to all files associated with the software unless
explicitly disclaimed in individual files. This copyright specifically does
not apply to the related textbook "The Visualization Toolkit" ISBN
013199837-4 published by Prentice Hall which is covered by its own copyright.

The authors hereby grant permission to use, copy, and distribute this
software and its documentation for any purpose, provided that existing
copyright notices are retained in all copies and that this notice is included
verbatim in any distributions. Additionally, the authors grant permission to
modify this software and its documentation for any purpose, provided that
such modifications are not distributed without the explicit consent of the
authors and that existing copyright notices are retained in all copies. Some
of the algorithms implemented by this software are patented, observe all
applicable patent law.

IN NO EVENT SHALL THE AUTHORS OR DISTRIBUTORS BE LIABLE TO ANY PARTY FOR
DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
OF THE USE OF THIS SOFTWARE, ITS DOCUMENTATION, OR ANY DERIVATIVES THEREOF,
EVEN IF THE AUTHORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

THE AUTHORS AND DISTRIBUTORS SPECIFICALLY DISCLAIM ANY WARRANTIES, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE, AND NON-INFRINGEMENT.  THIS SOFTWARE IS PROVIDED ON AN
"AS IS" BASIS, AND THE AUTHORS AND DISTRIBUTORS HAVE NO OBLIGATION TO PROVIDE
MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.


=========================================================================*/
// .NAME vtkAppendPolyData - appends one or more polygonal datasets together
// .SECTION Description
// vtkAppendPolyData is a filter that appends one of more polygonal datasets
// into a single polygonal dataset. All geometry is extracted and appended, 
// but point attributes (i.e., scalars, vectors, normals) are extracted 
// and appended only if all datasets have the point attributes available.
// (For example, if one dataset has scalars but another does not, scalars 
// will not be appended.)

// .SECTION See Also
// vtkAppendFilter

#ifndef __vtkAppendPolyData_h
#define __vtkAppendPolyData_h

#include "vtkPolyDataToPolyDataFilter.h"

class VTK_EXPORT vtkAppendPolyData : public vtkPolyDataToPolyDataFilter
{
public:
  static vtkAppendPolyData *New() {return new vtkAppendPolyData;}

  const char *GetClassName() {return "vtkAppendPolyData";}
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Add a dataset to the list of data to append.
  void AddInput(vtkPolyData *);

  // Description:
  // Remove a dataset from the list of data to append.
  void RemoveInput(vtkPolyData *);

  // Description:
  // Get any input of this filter.
  vtkPolyData *GetInput(int idx);
  
  // Description:
  // ParallelStreaming is for a particular application.
  // It causes this filter to ask for a different piece
  // from each of its inputs.  If all the inputs are the same,
  // then the output of this append filter is the whole dataset
  // pieced back together.  Duplicate points are create 
  // along the seams.  The purpose of this feature is to get 
  // data parallism at a course scale.  Each of the inputs
  // can be generated in a different process at the same time.
  vtkSetMacro(ParallelStreaming, int); 
  vtkGetMacro(ParallelStreaming, int); 
  vtkBooleanMacro(ParallelStreaming, int); 

  // hack until I get a real fix.
  void UpdateInformation();
  
protected:
  vtkAppendPolyData();
  ~vtkAppendPolyData();
  vtkAppendPolyData(const vtkAppendPolyData&) {};
  void operator=(const vtkAppendPolyData&) {};

  // Flag for selecting parallel streaming bejhavior
  int ParallelStreaming;

  // Usual data generation method
  void Execute();
  // Support for streaming (parallel)
  int ComputeInputUpdateExtents(vtkDataObject *output);

  // An efficient way to append data/cells.
  void AppendData(vtkDataArray *dest, vtkDataArray *src, int offset);
  int *AppendCells(int *pDest, vtkCellArray *src, int offset);

};

#endif


