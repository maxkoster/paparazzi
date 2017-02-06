
//custom linear algebra functions maybe later to paparazzi math
#define MAT33_TRANS(_mat1,_mat2) {     \
    MAT33_ELMT((_mat1),0,0) = MAT33_ELMT((_mat2),0,0);  \
    MAT33_ELMT((_mat1),0,1) = MAT33_ELMT((_mat2),1,0);  \
    MAT33_ELMT((_mat1),0,2) = MAT33_ELMT((_mat2),2,0);  \
    MAT33_ELMT((_mat1),1,0) = MAT33_ELMT((_mat2),0,1);  \
    MAT33_ELMT((_mat1),1,1) = MAT33_ELMT((_mat2),1,1);  \
    MAT33_ELMT((_mat1),1,2) = MAT33_ELMT((_mat2),2,1);  \
    MAT33_ELMT((_mat1),2,0) = MAT33_ELMT((_mat2),0,2);  \
    MAT33_ELMT((_mat1),2,1) = MAT33_ELMT((_mat2),1,2);  \
    MAT33_ELMT((_mat1),2,2) = MAT33_ELMT((_mat2),2,2);  \
  }

#define MAT33_MULT(_mat1,_mat2,_mat3) {     \
    MAT33_ELMT((_mat1),0,0) = MAT33_ELMT((_mat2),0,0);  \
    MAT33_ELMT((_mat1),0,1) = MAT33_ELMT((_mat2),1,0);  \
    MAT33_ELMT((_mat1),0,2) = MAT33_ELMT((_mat2),2,0);  \
    MAT33_ELMT((_mat1),1,0) = MAT33_ELMT((_mat2),0,1);  \
    MAT33_ELMT((_mat1),1,1) = MAT33_ELMT((_mat2),1,1);  \
    MAT33_ELMT((_mat1),1,2) = MAT33_ELMT((_mat2),2,1);  \
    MAT33_ELMT((_mat1),2,0) = MAT33_ELMT((_mat2),0,2);  \
    MAT33_ELMT((_mat1),2,1) = MAT33_ELMT((_mat2),1,2);  \
    MAT33_ELMT((_mat1),2,2) = MAT33_ELMT((_mat2),2,2);  \
  }