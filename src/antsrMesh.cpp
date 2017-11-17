
#include <algorithm>
#include <vector>
#include <string>
//#include <RcppANTsR.h>
#include <RcppDANTsR.h>

#include "antsUtilities.h"
#include "itkMesh.h"
#include "itkVtkPolyDataFileReader.h"


template< class MeshType >
typename MeshType::Pointer antsrMesh( itk::IdentifierType reserve )
{

  typename MeshType::Pointer mesh = MeshType::New();
  if ( reserve > 0 ) {
    mesh->GetPoints()->Reserve(reserve);
  }

  Rcpp::Rcout << "Created mesh: " << mesh->GetNumberOfPoints() << std::endl;

  return mesh;

}

//pixeltype, precision, dimension, type, isVector
RcppExport SEXP antsrMesh( SEXP r_precision, SEXP r_dimension, SEXP r_reserve)
{
try
{
  std::string precision = Rcpp::as< std::string >( r_precision );
  unsigned int dimension = Rcpp::as< int >( r_dimension );
  itk::IdentifierType reserve = Rcpp::as< itk::IdentifierType >( r_reserve );

  if ( (dimension < 2) || (dimension > 4) ) {
    Rcpp::stop("Unsupported dimension type - must be 2,3, or 4");
  }

  if ( precision=="double") {
    typedef double PrecisionType;
    if ( dimension == 2 ) {
      typedef itk::Mesh<PrecisionType,2> MeshType;
      return Rcpp::wrap( antsrMesh<MeshType>(reserve) );
    }
    else if ( dimension == 3 ) {
      typedef itk::Mesh<PrecisionType,3> MeshType;
      return Rcpp::wrap( antsrMesh<MeshType>(reserve) );
        }
    else if ( dimension == 4 ) {
      typedef itk::Mesh<PrecisionType,4> MeshType;
      return Rcpp::wrap( antsrMesh<MeshType>(reserve) );
    }
  }
  else if (precision=="float") {
    typedef float PrecisionType;
    if ( dimension == 2 ) {
      typedef itk::Mesh<PrecisionType,2> MeshType;
      return Rcpp::wrap( antsrMesh<MeshType>(reserve) );
    }
    else if ( dimension == 3 ) {
      typedef itk::Mesh<PrecisionType,3> MeshType;
      return Rcpp::wrap( antsrMesh<MeshType>(reserve) );
        }
    else if ( dimension == 4 ) {
      typedef itk::Mesh<PrecisionType,4> MeshType;
      return Rcpp::wrap( antsrMesh<MeshType>(reserve) );
    }
  }
  else {
    Rcpp::stop( "Unsupported precision type - must be 'float' or 'double'");
  }

  // Never reached
  return( Rcpp::wrap(NA_REAL) );

}
catch( itk::ExceptionObject & err )
  {
  Rcpp::Rcout << "ITK ExceptionObject caught !" << std::endl;
  Rcpp::Rcout << err << std::endl;
  Rcpp::stop("ITK exception caught");
  }
catch( const std::exception& exc )
  {
  forward_exception_to_r( exc ) ;
  }
catch(...)
  {
	Rcpp::stop("c++ exception (unknown reason)");
  }
return Rcpp::wrap(NA_REAL); //not reached
}


template< class MeshType >
SEXP
antsrMesh_GetNumberOfPoints( SEXP rMesh )
{
  typedef typename MeshType::Pointer MeshPointerType;
  MeshPointerType mesh = Rcpp::as<MeshPointerType>( rMesh );
  return( Rcpp::wrap(mesh->GetNumberOfPoints()) );
}

//pixeltype, precision, dimension, type, isVector
RcppExport SEXP antsrMesh_GetNumberOfPoints( SEXP r_mesh )
{
try
{
  Rcpp::S4 rMesh( r_mesh );
  std::string precision = rMesh.slot("precision");
  unsigned int dimension = rMesh.slot("dimension");

  if ( (dimension < 2) || (dimension > 4) ) {
    Rcpp::stop("Unsupported dimension type - must be 2,3, or 4");
  }

  if ( precision=="double") {
    typedef double PrecisionType;
    if ( dimension == 2 ) {
      typedef itk::Mesh<PrecisionType,2> MeshType;
      return antsrMesh_GetNumberOfPoints<MeshType>(r_mesh);
    }
    else if ( dimension == 3 ) {
      typedef itk::Mesh<PrecisionType,3> MeshType;
      return antsrMesh_GetNumberOfPoints<MeshType>(r_mesh);
    }
    else if ( dimension == 4 ) {
      typedef itk::Mesh<PrecisionType,4> MeshType;
      return antsrMesh_GetNumberOfPoints<MeshType>(r_mesh);
    }
  }
  else if (precision=="float") {
    typedef float PrecisionType;
    if ( dimension == 2 ) {
      typedef itk::Mesh<PrecisionType,2> MeshType;
      return antsrMesh_GetNumberOfPoints<MeshType>(r_mesh);
    }
    else if ( dimension == 3 ) {
      typedef itk::Mesh<PrecisionType,3> MeshType;
      return antsrMesh_GetNumberOfPoints<MeshType>(r_mesh);
        }
    else if ( dimension == 4 ) {
      typedef itk::Mesh<PrecisionType,4> MeshType;
      return antsrMesh_GetNumberOfPoints<MeshType>(r_mesh);
    }
  }
  else {
    Rcpp::stop( "Unsupported precision type - must be 'float' or 'double'");
  }

  // Never reached
  return( Rcpp::wrap(NA_REAL) );

}
catch( itk::ExceptionObject & err )
  {
  Rcpp::Rcout << "ITK ExceptionObject caught !" << std::endl;
  Rcpp::Rcout << err << std::endl;
  Rcpp::stop("ITK exception caught");
  }
catch( const std::exception& exc )
  {
  forward_exception_to_r( exc ) ;
  }
catch(...)
  {
	Rcpp::stop("c++ exception (unknown reason)");
  }
return Rcpp::wrap(NA_REAL); //not reached
}

template< class MeshType >
SEXP
antsrMesh_GetPoint( SEXP r_mesh, SEXP r_identifier )
{
  Rcpp::S4 rMesh( r_mesh );
  unsigned int dimension = rMesh.slot("dimension");

  typedef typename MeshType::Pointer MeshPointerType;
  MeshPointerType mesh = Rcpp::as<MeshPointerType>( rMesh );
  itk::IdentifierType id = Rcpp::as<itk::IdentifierType>( r_identifier );

  Rcpp::NumericVector pt( dimension );
  typename MeshType::PointType itkPoint;
  mesh->GetPoint(id, &itkPoint);

  for ( unsigned int i=0; i<dimension; i++ ) {
    pt[i] = itkPoint[i];
  }

  return( Rcpp::wrap(pt) );
}

//pixeltype, precision, dimension, type, isVector
RcppExport SEXP antsrMesh_GetPoint( SEXP r_mesh, SEXP r_identifier )
{
try
{
  Rcpp::S4 rMesh( r_mesh );
  std::string precision = rMesh.slot("precision");
  unsigned int dimension = rMesh.slot("dimension");

  if ( (dimension < 2) || (dimension > 4) ) {
    Rcpp::stop("Unsupported dimension type - must be 2,3, or 4");
  }

  if ( precision=="double") {
    typedef double PrecisionType;
    if ( dimension == 2 ) {
      typedef itk::Mesh<PrecisionType,2> MeshType;
      return antsrMesh_GetPoint<MeshType>(r_mesh, r_identifier);
    }
    else if ( dimension == 3 ) {
      typedef itk::Mesh<PrecisionType,3> MeshType;
      return antsrMesh_GetPoint<MeshType>(r_mesh, r_identifier);
    }
    else if ( dimension == 4 ) {
      typedef itk::Mesh<PrecisionType,4> MeshType;
      return antsrMesh_GetPoint<MeshType>(r_mesh, r_identifier);
    }
  }
  else if (precision=="float") {
    typedef float PrecisionType;
    if ( dimension == 2 ) {
      typedef itk::Mesh<PrecisionType,2> MeshType;
      return antsrMesh_GetPoint<MeshType>(r_mesh, r_identifier);
    }
    else if ( dimension == 3 ) {
      typedef itk::Mesh<PrecisionType,3> MeshType;
      return antsrMesh_GetPoint<MeshType>(r_mesh, r_identifier);
        }
    else if ( dimension == 4 ) {
      typedef itk::Mesh<PrecisionType,4> MeshType;
      return antsrMesh_GetPoint<MeshType>(r_mesh, r_identifier);
    }
  }
  else {
    Rcpp::stop( "Unsupported precision type - must be 'float' or 'double'");
  }

  // Never reached
  return( Rcpp::wrap(NA_REAL) );

}
catch( itk::ExceptionObject & err )
  {
  Rcpp::Rcout << "ITK ExceptionObject caught !" << std::endl;
  Rcpp::Rcout << err << std::endl;
  Rcpp::stop("ITK exception caught");
  }
catch( const std::exception& exc )
  {
  forward_exception_to_r( exc ) ;
  }
catch(...)
  {
	Rcpp::stop("c++ exception (unknown reason)");
  }
return Rcpp::wrap(NA_REAL); //not reached
}

template< class MeshType >
SEXP
antsrMesh_GetPoints( SEXP r_mesh, SEXP r_identifiers )
{
  Rcpp::S4 rMesh( r_mesh );
  unsigned int dimension = rMesh.slot("dimension");

  typedef typename MeshType::Pointer MeshPointerType;
  MeshPointerType mesh = Rcpp::as<MeshPointerType>( rMesh );
  Rcpp::NumericVector ids = Rcpp::as<Rcpp::NumericVector>(r_identifiers);

  typename MeshType::PointType itkPoint;
  itk::IdentifierType nPoints = mesh->GetNumberOfPoints();
  if ( ids.size() != 0 ) {
    nPoints = ids.size();
  }
  Rcpp::NumericMatrix pts( nPoints, dimension);

  for ( itk::IdentifierType i=0; i<nPoints; i++ ) {

    itk::IdentifierType id = i;
    if (ids.size() != 0 ) {
      id = ids[i];
    }

    mesh->GetPoint(id, &itkPoint);
    for ( unsigned int j=0; j<dimension; j++) {
      pts(i,j) = itkPoint[j];
    }
  }

  return( Rcpp::wrap(pts) );
}

//pixeltype, precision, dimension, type, isVector
RcppExport SEXP antsrMesh_GetPoints( SEXP r_mesh, SEXP r_identifiers )
{
try
{
  Rcpp::S4 rMesh( r_mesh );
  std::string precision = rMesh.slot("precision");
  unsigned int dimension = rMesh.slot("dimension");

  if ( (dimension < 2) || (dimension > 4) ) {
    Rcpp::stop("Unsupported dimension type - must be 2,3, or 4");
  }

  if ( precision=="double") {
    typedef double PrecisionType;
    if ( dimension == 2 ) {
      typedef itk::Mesh<PrecisionType,2> MeshType;
      return antsrMesh_GetPoints<MeshType>(r_mesh, r_identifiers);
    }
    else if ( dimension == 3 ) {
      typedef itk::Mesh<PrecisionType,3> MeshType;
      return antsrMesh_GetPoints<MeshType>(r_mesh, r_identifiers);
    }
    else if ( dimension == 4 ) {
      typedef itk::Mesh<PrecisionType,4> MeshType;
      return antsrMesh_GetPoints<MeshType>(r_mesh, r_identifiers);
    }
  }
  else if (precision=="float") {
    typedef float PrecisionType;
    if ( dimension == 2 ) {
      typedef itk::Mesh<PrecisionType,2> MeshType;
      return antsrMesh_GetPoints<MeshType>(r_mesh, r_identifiers);
    }
    else if ( dimension == 3 ) {
      typedef itk::Mesh<PrecisionType,3> MeshType;
      return antsrMesh_GetPoints<MeshType>(r_mesh, r_identifiers);
        }
    else if ( dimension == 4 ) {
      typedef itk::Mesh<PrecisionType,4> MeshType;
      return antsrMesh_GetPoints<MeshType>(r_mesh, r_identifiers);
    }
  }
  else {
    Rcpp::stop( "Unsupported precision type - must be 'float' or 'double'");
  }

  // Never reached
  return( Rcpp::wrap(NA_REAL) );

}
catch( itk::ExceptionObject & err )
  {
  Rcpp::Rcout << "ITK ExceptionObject caught !" << std::endl;
  Rcpp::Rcout << err << std::endl;
  Rcpp::stop("ITK exception caught");
  }
catch( const std::exception& exc )
  {
  forward_exception_to_r( exc ) ;
  }
catch(...)
  {
	Rcpp::stop("c++ exception (unknown reason)");
  }
return Rcpp::wrap(NA_REAL); //not reached
}


template< class MeshType >
SEXP
antsrMesh_SetPoint( SEXP r_mesh, SEXP r_identifier, SEXP r_point )
{
  Rcpp::S4 rMesh( r_mesh );
  unsigned int dimension = rMesh.slot("dimension");

  typedef typename MeshType::Pointer MeshPointerType;
  MeshPointerType mesh = Rcpp::as<MeshPointerType>( rMesh );
  itk::IdentifierType id = Rcpp::as<itk::IdentifierType>( r_identifier );

  Rcpp::NumericVector pt = Rcpp::as<Rcpp::NumericVector>( r_point );
  if ( pt.size() != dimension ) {
    Rcpp::stop("Point has incorrect size");
  }

  typename MeshType::PointType itkPoint;

  for ( unsigned int i=0; i<dimension; i++ ) {
    itkPoint[i] = pt(i);
  }

  mesh->SetPoint(id, itkPoint);

  return( Rcpp::wrap(NA_REAL) );
}

//pixeltype, precision, dimension, type, isVector
RcppExport SEXP antsrMesh_SetPoint( SEXP r_mesh, SEXP r_identifier, SEXP r_point )
{
try
{
  Rcpp::S4 rMesh( r_mesh );
  std::string precision = rMesh.slot("precision");
  unsigned int dimension = rMesh.slot("dimension");

  if ( (dimension < 2) || (dimension > 4) ) {
    Rcpp::stop("Unsupported dimension type - must be 2,3, or 4");
  }

  if ( precision=="double") {
    typedef double PrecisionType;
    if ( dimension == 2 ) {
      typedef itk::Mesh<PrecisionType,2> MeshType;
      return antsrMesh_SetPoint<MeshType>(r_mesh, r_identifier, r_point);
    }
    else if ( dimension == 3 ) {
      typedef itk::Mesh<PrecisionType,3> MeshType;
      return antsrMesh_SetPoint<MeshType>(r_mesh, r_identifier, r_point);
    }
    else if ( dimension == 4 ) {
      typedef itk::Mesh<PrecisionType,4> MeshType;
      return antsrMesh_SetPoint<MeshType>(r_mesh, r_identifier, r_point);
    }
  }
  else if (precision=="float") {
    typedef float PrecisionType;
    if ( dimension == 2 ) {
      typedef itk::Mesh<PrecisionType,2> MeshType;
      return antsrMesh_SetPoint<MeshType>(r_mesh, r_identifier, r_point);
    }
    else if ( dimension == 3 ) {
      typedef itk::Mesh<PrecisionType,3> MeshType;
      return antsrMesh_SetPoint<MeshType>(r_mesh, r_identifier, r_point);
        }
    else if ( dimension == 4 ) {
      typedef itk::Mesh<PrecisionType,4> MeshType;
      return antsrMesh_SetPoint<MeshType>(r_mesh, r_identifier, r_point);
    }
  }
  else {
    Rcpp::stop( "Unsupported precision type - must be 'float' or 'double'");
  }

  // Never reached
  return( Rcpp::wrap(NA_REAL) );

}
catch( itk::ExceptionObject & err )
  {
  Rcpp::Rcout << "ITK ExceptionObject caught !" << std::endl;
  Rcpp::Rcout << err << std::endl;
  Rcpp::stop("ITK exception caught");
  }
catch( const std::exception& exc )
  {
  forward_exception_to_r( exc ) ;
  }
catch(...)
  {
	Rcpp::stop("c++ exception (unknown reason)");
  }
return Rcpp::wrap(NA_REAL); //not reached
}

template< class MeshType >
SEXP
antsrMesh_ReadVTK( SEXP r_filename )
{
  typedef typename MeshType::Pointer      MeshPointerType;
  typedef itk::VtkPolyDataFileReader<MeshType>  ReaderType;

  std::string filename = Rcpp::as<std::string>( r_filename );

  typename ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( filename.c_str() );
  reader->Update();
  MeshPointerType mesh = reader->GetOutput();

  Rcpp::Rcout << "Number of points in mesh: " << mesh->GetNumberOfPoints() << std::endl;

  typename ReaderType::LineSetType * lines = reader->GetLines();
  Rcpp::Rcout << "Number of lines: " << lines->Size() << std::endl;

    typename ReaderType::LineSetType * poly = reader->GetPolygons();
    Rcpp::Rcout << "Number of polygons: " << poly->Size() << std::endl;

  return Rcpp::wrap(mesh);

  //MeshPointerType mesh = Rcpp::as<MeshPointerType>( rMesh );
  //return( Rcpp::wrap(mesh->GetNumberOfPoints()) );
}

//pixeltype, precision, dimension, type, isVector
RcppExport SEXP antsrMesh_ReadVTK( SEXP r_filename, SEXP r_dimension, SEXP r_pixeltype )
{
try
{
  std::string precision = Rcpp::as<std::string>(r_pixeltype);
  unsigned int dimension = Rcpp::as<unsigned int>(r_dimension);

  if ( (dimension < 2) || (dimension > 4) ) {
    Rcpp::stop("Unsupported dimension type - must be 2,3, or 4");
  }

  if ( precision=="double") {
    typedef double PrecisionType;
    if ( dimension == 2 ) {
      typedef itk::Mesh<PrecisionType,2> MeshType;
      return antsrMesh_ReadVTK<MeshType>(r_filename);
    }
    else if ( dimension == 3 ) {
      typedef itk::Mesh<PrecisionType,3> MeshType;
      return antsrMesh_ReadVTK<MeshType>(r_filename);
    }
    else if ( dimension == 4 ) {
      typedef itk::Mesh<PrecisionType,4> MeshType;
      return antsrMesh_ReadVTK<MeshType>(r_filename);
    }
  }
  else if (precision=="float") {
    typedef float PrecisionType;
    if ( dimension == 2 ) {
      typedef itk::Mesh<PrecisionType,2> MeshType;
      return antsrMesh_ReadVTK<MeshType>(r_filename);
    }
    else if ( dimension == 3 ) {
      typedef itk::Mesh<PrecisionType,3> MeshType;
      return antsrMesh_ReadVTK<MeshType>(r_filename);
        }
    else if ( dimension == 4 ) {
      typedef itk::Mesh<PrecisionType,4> MeshType;
      return antsrMesh_ReadVTK<MeshType>(r_filename);
    }
  }
  else {
    Rcpp::stop( "Unsupported precision type - must be 'float' or 'double'");
  }

  // Never reached
  return( Rcpp::wrap(NA_REAL) );

}
catch( itk::ExceptionObject & err )
  {
  Rcpp::Rcout << "ITK ExceptionObject caught !" << std::endl;
  Rcpp::Rcout << err << std::endl;
  Rcpp::stop("ITK exception caught");
  }
catch( const std::exception& exc )
  {
  forward_exception_to_r( exc ) ;
  }
catch(...)
  {
	Rcpp::stop("c++ exception (unknown reason)");
  }
return Rcpp::wrap(NA_REAL); //not reached
}