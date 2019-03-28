namespace Eigen {}
namespace SolAR{namespace datastructure{
	namespace Maths {
		/*
		%attributeref(Matrix, int, cols);
		%attributeref(Matrix, int, rows);
		%attributeref(Matrix, int, size);
		%attributeref(Matrix, int, colStride);
		%attributeref(Matrix, int, innerStride);
		%attributeref(Matrix, int, outerStride);
		%attributeref(Matrix, int, rowStride);
		*/
		template <class Scalar, int Rows, int Cols, int ColOrRowMajor = Eigen::RowMajor>
		class Matrix
		{
// https://eigen.tuxfamily.org/dox/classEigen_1_1Matrix.html
		public:
// Matrix
			~Matrix();
			Matrix();
// PlainObjectBase
			const Scalar & coeff(int rowId, int colId) const;
			/*
			//Scalar* data();
// MatrixBase
			//void adjointInPlace ();
			Scalar determinant() const;
			int diagonalSize () const;
			void normalize();
			void stableNormalize ();
			Scalar trace() const;
// DenseBase
			bool all() const;
			bool allFinite() const;
			bool any() const;
			int count() const;
			void fill(const Scalar& value);
			bool hasNaN() const;
			int innerSize () const;
			Scalar mean() const;
			int nonZeros() const;
			int outerSize () const;
			Scalar prod() const;
			void reverseInPlace ();
			Scalar sum() const;
			//void transposeInPlace ();
// DenseCoeffsBase
			int colStride() const;
			int innerStride() const;
			int outerStride() const;
			int rowStride() const;
			*/
// EigenBase
			int cols() const;
			int rows() const;
			int size() const;
		};
		
		template <class T, int Rows>
		typedef Matrix<T, Dim, 1> Vector;
		
		//typedef Matrix<float, 3, 1> Vector3f;
	}
	
	template <class T, int Dim>
	typedef Maths::Matrix<T, Dim, 1> Vector;
	
	typedef Maths::Matrix<float, 3, 1> Vector3f;
	
	template <class Scalar, int Dim>
	class Transform
	{
// https://eigen.tuxfamily.org/dox/classEigen_1_1Transform.html
	public:
		~Transform ();
		Transform ();
		static const Transform Identity ();
		const Maths::Matrix<Scalar, Dim, Dim> rotation () const;
		const Maths::Matrix<Scalar, Dim, 1> translation () const;
		/*
		void setIdentity ();
		void makeAffine ();
		Transform & prescale (const Scalar &s);
		Transform & scale (const Scalar &s);
		//TranslationPart translation ();
		*/
	};
	
	%attributeref(Translation, Scalar, x);
	%attributeref(Translation, Scalar, y);
	%attributeref(Translation, Scalar, z);
	template <class Scalar, int Dim>
	class Translation
	{
// https://eigen.tuxfamily.org/dox/classEigen_1_1Translation.html
	public:
		~Translation ();
		Translation ();
		//Translation (const VectorType &vector);
		//Translation<Scalar, Dim> inverse () const;
		//Scalar x () const;
		Scalar & x ();
		//Scalar y () const;
		Scalar & y ();
		//Scalar z () const;
		Scalar & z ();
	};
	
	%attributeref(Quaternion, Scalar, w);
	%attributeref(Quaternion, Scalar, x);
	%attributeref(Quaternion, Scalar, y);
	%attributeref(Quaternion, Scalar, z);
	template <class Scalar>
	class Quaternion
	{
// https://eigen.tuxfamily.org/dox/classEigen_1_1Quaternion.html
	public:
// Quaternion
		~Quaternion();
		Quaternion ();
		Quaternion (const Scalar &w, const Scalar &x, const Scalar &y, const Scalar &z);
		Scalar& w();
		Scalar& x();
		Scalar& y();
		Scalar& z();
		/*
		//static Quaternion<Scalar> UnitRandom ();
		Quaternion<Scalar> conjugate () const;
		Quaternion<Scalar> inverse () const;
		Scalar norm () const;
		void normalize ();
		Quaternion<Scalar> normalized () const;
		Scalar squaredNorm () const;
		//Matrix3 toRotationMatrix () const;
// RotationBase
		//RotationMatrixType matrix () const;
		*/
	};
}}

%define DATASTRUCT(NAME, TYPE...)
%shared_ptr(SolAR::datastructure::TYPE)
%template(NAME) SolAR::datastructure::TYPE;
%enddef

DATASTRUCT(Transform2Df, Transform<float, 2>)
DATASTRUCT(Transform3Df, Transform<float, 3>)

/*
%ignore SolAR::datastructure::Translation<float, 2>::z();
DATASTRUCT(Translation2Df, Translation<float, 2>)
DATASTRUCT(Translation3Df, Translation<float, 3>)

DATASTRUCT(Quaternionf, Quaternion<float>)
*/

%define MATRIX(NAME, ROWS, COLS, TYPE)
DATASTRUCT(NAME, Maths::Matrix<TYPE, ROWS, COLS>)
%enddef

/*
MATRIX(ProjectionMatrix, 3, 4, float)
MATRIX(RotationMatrixf, 3, 3, float)
MATRIX(CamCalibration, 3, 3, float)
MATRIX(CamDistortion, 5, 1, float)
MATRIX(PoseMatrix, 4, 4, float)
*/

MATRIX(Matrix2x2f, 2, 2, float)
MATRIX(Matrix3x3f, 3, 3, float)

%define VECTOR(NAME, SIZE, TYPE)
MATRIX(NAME, SIZE, 1, TYPE)
//%shared_ptr(SolAR::datastructure::Vector<TYPE, SIZE>)
%template(NAME) SolAR::datastructure::Vector<TYPE, SIZE>;
%enddef

VECTOR(Vector2f, 2, float)
VECTOR(Vector3f, 3, float)
VECTOR(Vector5f, 5, float)

VECTOR(Vector2i, 2, int)
VECTOR(Vector3i, 3, int)
