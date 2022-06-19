#pragma once

#include <fstream>
#include <cassert>

namespace image
{

namespace impl
{

template<typename T>  
void brightePixel(Image<T>& a_image, int& a_factor, size_t& a_row, size_t& a_column)
{
    T pixel = a_image.getPixel(a_row, a_column);
    pixel += a_factor;
    a_image.setPixel(a_row, a_column, pixel);
}

template<typename T> 
void changePixelColorScale(Image<T>& a_imageObject, T& a_scale, size_t& a_row, size_t& a_column)
{
    T pixel = a_imageObject.getPixel(a_row, a_column);
    float percent = pixel/(float)a_imageObject.scale();
    T newPixel = percent*a_scale;
    a_imageObject.setPixel(a_row, a_column, newPixel);
}

template<typename T> 
void makePixelsArray(Image<T>& a_imageObject, T*& a_pixelsArray, int& a_by, size_t& a_row, size_t a_column, int a_columnsOfset)
{
    for(int i = 0; i < a_by; ++i)
    {
        for(int j = 0; j < a_by; ++j)
        {
            a_pixelsArray[i*a_by + j] =  a_imageObject.getPixel(a_row + i, a_column + j*a_columnsOfset);
        }
    }
}

template<typename T> 
T calculateAverage(T*& a_pixelsArray , int& a_by)
{
    T ava = 0;
    for(int i = 0; i < a_by*a_by; ++i)
    {
        ava += a_pixelsArray[i];
    }
    return ava/=(a_by*a_by);
}

template<typename T> 
void setNewPixels(Image<T>& a_imageObject, T& a_average, size_t& a_row, size_t a_column, int& a_by, int a_columnsOfset)
{
    for(int i = 0; i < a_by; ++i)
    {
        for(int j = 0; j < a_by; ++j)
        {
           a_imageObject.setPixel(a_row + i, a_column + j*a_columnsOfset, a_average); 
        }
    }
}

template<typename T> 
void reducePixel(Image<T>& a_imageObject, size_t& a_row, size_t& a_column, int a_by, T*& a_pixelsArray)
{
    makePixelsArray(a_imageObject, a_pixelsArray, a_by, a_row, a_column, 1);
    T average =  calculateAverage(a_pixelsArray, a_by);
    setNewPixels(a_imageObject, average, a_row, a_column, a_by, 1);
}

template<typename T> 
void reduceColoredPixel(Image<T>& a_imageObject, size_t& a_row, size_t& a_column, int& a_by, T*& a_pixelsArray)
{
    makePixelsArray(a_imageObject, a_pixelsArray, a_by, a_row, a_column, 3);
    T average =  calculateAverage(a_pixelsArray, a_by);
    setNewPixels(a_imageObject, average, a_row, a_column, a_by, 3);

    makePixelsArray(a_imageObject, a_pixelsArray, a_by, a_row, a_column + 1, 3);
    average =  calculateAverage(a_pixelsArray, a_by);
    setNewPixels(a_imageObject, average, a_row, a_column + 1, a_by, 3);

    makePixelsArray(a_imageObject, a_pixelsArray, a_by, a_row, a_column + 2, 3);
    average =  calculateAverage(a_pixelsArray, a_by);
    setNewPixels(a_imageObject, average, a_row, a_column + 2, a_by, 3);
}

size_t CalculateArraySize(const std::string& a_format, const size_t& a_rows,  size_t& a_columns)
{
    if(a_format == "P3")
       return a_rows*a_columns*3; 

    else
       return a_rows*a_columns; 
}

size_t CalculateRowsOffset(const std::string& a_format, const size_t& a_rows,  const size_t& m_rows)
{
    if(a_format == "P3")
       return a_rows*m_rows*3 ; 

    else
       return a_rows*m_rows; 
}

void setColumnSize(const std::string& a_format, size_t& a_column)
{
    if(a_format == "P3")
        a_column *= 3;
}

template<typename T> 
void reducePixels(Image<T>& a_imageObject, size_t a_rows, size_t a_columns, int a_by)
{
    T* pixelsArray = new T[a_by*a_by];
    for(size_t i = 0 ; i < a_rows; i += a_by)
    {
        for(size_t j = 0 ; j < a_columns; j += a_by)
        {
            impl::reducePixel(a_imageObject, i, j, a_by, pixelsArray);
        }
    }
    delete[] pixelsArray;
}

template<typename T> 
void reduceColoredPixels(Image<T>& a_imageObject, size_t a_rows, size_t a_columns, int a_by)
{
    T* pixelsArray = new T[a_by*a_by];
    for(size_t i = 0 ; i < a_rows; i += a_by)
    {
        for(size_t j = 0 ; j < a_columns; j += a_by*3)
        {
            impl::reduceColoredPixel(a_imageObject, i, j, a_by, pixelsArray);
        }
    }
    delete[] pixelsArray;
}

template<typename T> 
void setPixel(Image<T>& a_imageObject, Image<T>& newImage, size_t a_rows, size_t a_columns, float*& a_multipliers)
{
    T setPixel = a_imageObject.getPixel(a_rows-1, a_columns -1)*a_multipliers[0];
    setPixel += a_imageObject.getPixel(a_rows+1, a_columns +1)*a_multipliers[0];
    setPixel += a_imageObject.getPixel(a_rows+1, a_columns -1)*a_multipliers[0];
    setPixel += a_imageObject.getPixel(a_rows-1, a_columns +1)*a_multipliers[0];
    setPixel += a_imageObject.getPixel(a_rows-1, a_columns)*a_multipliers[1];
    setPixel += a_imageObject.getPixel(a_rows+1, a_columns)*a_multipliers[1];
    setPixel += a_imageObject.getPixel(a_rows, a_columns-1)*a_multipliers[1];
    setPixel += a_imageObject.getPixel(a_rows, a_columns+1)*a_multipliers[1];
    setPixel += a_imageObject.getPixel(a_rows, a_columns)*a_multipliers[2];
    newImage.setPixel(a_rows, a_columns, setPixel);
}

template<typename T> 
void setSingelColorPixel(Image<T>& a_imageObject, Image<T>& newImage, size_t a_rows, size_t a_columns, float*& a_multipliers)
{
    T setPixel = a_imageObject.getPixel(a_rows-1, a_columns -3)*a_multipliers[0];
    setPixel += a_imageObject.getPixel(a_rows+1, a_columns +3)*a_multipliers[0];
    setPixel += a_imageObject.getPixel(a_rows+1, a_columns -3)*a_multipliers[0];
    setPixel += a_imageObject.getPixel(a_rows-1, a_columns +3)*a_multipliers[0];
    setPixel += a_imageObject.getPixel(a_rows-1, a_columns)*a_multipliers[1];
    setPixel += a_imageObject.getPixel(a_rows+1, a_columns)*a_multipliers[1];
    setPixel += a_imageObject.getPixel(a_rows, a_columns-3)*a_multipliers[1];
    setPixel += a_imageObject.getPixel(a_rows, a_columns+3)*a_multipliers[1];
    setPixel += a_imageObject.getPixel(a_rows, a_columns)*a_multipliers[2];
    newImage.setPixel(a_rows, a_columns, setPixel);
}

template<typename T> 
void setColoredPixel(Image<T>& a_imageObject, Image<T>& newImage, size_t a_rows, size_t a_columns, float*& a_multipliers)
{
    setSingelColorPixel(a_imageObject, newImage, a_rows, a_columns, a_multipliers);
    setSingelColorPixel(a_imageObject, newImage, a_rows, a_columns + 1, a_multipliers);
    setSingelColorPixel(a_imageObject, newImage, a_rows, a_columns + 2, a_multipliers);
}

template<typename T> 
void setBlackAndwhite(Image<T>& a_imageObject, Image<T>& newImage, size_t a_rows, size_t a_columns, float a_multipliers[3])
{
    for(size_t i = 1 ; i < a_rows; ++i)
    {
        for(size_t j = 1 ; j < a_columns; ++j)
        {
            setPixel(a_imageObject, newImage, i, j, a_multipliers);
        }
    }
}

template<typename T> 
void setColored(Image<T>& a_imageObject, Image<T>& newImage, size_t a_rows, size_t a_columns, float a_multipliers[3])
{
    for(size_t i = 1 ; i < a_rows; ++i)
    {
        for(size_t j = 3 ; j < a_columns; j+=2)
        {
            setColoredPixel(a_imageObject, newImage, i, j, a_multipliers);
        }
    }
}


}// impl namespace

template<typename T>
Image<T>::Image(size_t a_rows, size_t a_columns, std::string a_format, int a_colorScale)
: m_rows(a_rows)
, m_columns (a_columns)
, m_format(a_format)
, m_colorScale(a_colorScale)
, m_pixels(new T[impl::CalculateArraySize(m_format, m_rows, m_columns)])
{

}

template<typename T>
Image<T>::Image(Image const& a_source)
: m_rows(a_source.m_rows)
, m_columns (a_source.m_columns)
, m_format(a_source.m_format)
, m_colorScale(a_source.m_colorScale)
, m_pixels(new T[impl::CalculateArraySize(m_format, m_rows, m_columns)])
{
    size_t size = impl::CalculateArraySize(m_format, m_rows, m_columns);
    std::copy(a_source.m_pixels, a_source.m_pixels + size, m_pixels);
}

template<typename T>
Image<T>::Image(Image&& a_source)
: m_rows(a_source.m_rows)
, m_columns (a_source.m_columns)
, m_format(a_source.m_format)
, m_colorScale(a_source.m_colorScale)
, m_pixels(a_source.m_pixels)
{
    a_source.m_pixels = nullptr;
    a_source.m_rows = 0;
}

template<typename T>
Image<T>& Image<T>::operator=(Image<T> const& a_source)
{
    if(*this == a_source){return *this;}
    Image<T> temp(a_source);
    swap(temp);
    return *this;
}

template<typename T>
Image<T>& Image<T>::operator=(Image<T>&& a_source)
{
    if(*this == a_source){return *this;}
    Image<T> temp(a_source);
    swap(temp);
    return *this;
}

template<typename T>
Image<T>::~Image()
{
    delete[] m_pixels;
} 

template<typename T>
T Image<T>::getPixel(size_t a_rows, size_t a_columns)const
{
    assert(a_rows <= m_rows || a_columns <= m_columns);
    size_t rowsOffset = impl::CalculateRowsOffset(m_format, a_rows, m_rows);
    return m_pixels[rowsOffset + a_columns];
}

template<typename T>
void Image<T>::setPixel(size_t a_rows, size_t a_columns, T a_pixel)
{
    assert(a_rows <= m_rows || a_columns <= m_columns);
    if(a_pixel > m_colorScale || a_pixel < 0)
        return;

    size_t rowsOffset = impl::CalculateRowsOffset(m_format, a_rows, m_rows);
    m_pixels[rowsOffset + a_columns] = a_pixel;
}

template<typename T>
void Image<T>::swap(Image<T>& a_source)
{
    std::swap(a_source.m_rows, this->m_rows);
    std::swap(a_source.m_columns, this->m_columns);
    std::swap(a_source.m_format, this->m_format);
    std::swap(a_source.m_colorScale, this->m_colorScale);
    std::swap(a_source.m_pixels, this->m_pixels);
}

template<typename T>
void Image<T>::setScale(int a_colorScale)
{
    m_colorScale = a_colorScale;
}

template<typename T>
size_t Image<T>::rows()const
{
    return m_rows;
}

template<typename T>
size_t Image<T>::columns()const
{
    return m_columns;
}

template<typename T>
T Image<T>::scale()const
{
    return m_colorScale;
}

template<typename T>
std::string Image<T>::format()const
{
    return m_format;
}

template<typename T>
bool Image<T>::operator==(Image const& a_source)
{
    return m_pixels == a_source.m_pixels;
}

template<typename T>  
Image<T> read (std::ifstream& a_imageFile)
{
    std::string format;
    size_t rows, columns;
    T colorScale;
    a_imageFile >> format >> rows >> columns >> colorScale;
    Image<T> imageObject(rows, columns, format, colorScale);

    impl::setColumnSize(format, columns);

    rows = 0;
    T pixel;
    while(rows < image.rows())
    {
        for(size_t i = 0; i < columns; ++i)
        {
            a_imageFile >> pixel;
            imageObject.setPixel(rows, i, pixel);
        }
        ++rows;
    }
    return imageObject;
}

template<typename T>  
void save (Image<T>& a_imageObject, std::ofstream& a_imagefile)
{
    a_imagefile << a_imageObject.format() << "\n";
    a_imagefile << a_imageObject.rows() << " " << a_imageObject.columns() << "\n";
    a_imagefile << a_imageObject.scale() << "\n";

    const size_t rows = a_imageObject.rows();
    size_t columns = a_imageObject.columns();
    impl::setColumnSize(a_imageObject.format(), columns);

    for(size_t i = 0 ; i < rows; ++i)
    {
        for(size_t j = 0 ; j < columns; ++j)
        {
            a_imagefile << a_imageObject.getPixel(i, j) << " ";
        }
        a_imagefile << "\n";
    }
}

template<typename T>  
void brighten (Image<T>& a_imageObject, int a_factor)
{
    const size_t rows = a_imageObject.rows();
    size_t columns = a_imageObject.columns();
    impl::setColumnSize(a_imageObject.format(), columns);

    for(size_t i = 0 ; i < rows; ++i)
    {
        for(size_t j = 0 ; j < columns; ++j)
        {
           impl::brightePixel(a_imageObject, a_factor, i, j);
        }
    }
}

template<typename T> 
void changeColorScale(Image<T>& a_imageObject, T a_scale)
{
    const size_t rows = a_imageObject.rows();
    size_t columns = a_imageObject.columns();
    impl::setColumnSize(a_imageObject.format(), columns);

    for(size_t i = 0 ; i < rows; ++i)
    {
        for(size_t j = 0 ; j < columns; ++j)
        {
            impl::changePixelColorScale(a_imageObject, a_scale, i, j);
        }
    }
    a_imageObject.setScale(a_scale);
}

template<typename T> 
void reducePixels(Image<T>& a_imageObject, int a_by)
{
    const size_t rows = a_imageObject.rows();
    size_t columns = a_imageObject.columns();
    impl::setColumnSize(a_imageObject.format(), columns);

    if(a_imageObject.format() == "P2")
        impl::reducePixels(a_imageObject, rows -(a_by-1), columns -(a_by-1), a_by);
    else
        impl::reduceColoredPixels(a_imageObject, rows -(a_by-1), columns -3*(a_by) -1, a_by);

}

template<typename T> 
Image<T> blur(Image<T>& a_imageObject)
{
    const size_t rows = a_imageObject.rows();
    size_t columns = a_imageObject.columns();
    impl::setColumnSize(a_imageObject.format(), columns);
    Image<T> blurImage = a_imageObject;
    float multipliers[3] = {0.0625, 0.125, 0.25};

    if(a_imageObject.format() == "P2")
        impl::setBlackAndwhite(a_imageObject, blurImage, rows - 1, columns - 1, multipliers);
    else
        impl::setColored(a_imageObject, blurImage, rows - 1, columns - 5, multipliers);

    return blurImage;
}

template<typename T> 
Image<T> sharp(Image<T>& a_imageObject)
{
    const size_t rows = a_imageObject.rows();
    size_t columns = a_imageObject.columns();
    impl::setColumnSize(a_imageObject.format(), columns);
    Image<T> sharpImage = a_imageObject;
    float multipliers[3] = {0 , -1, 5};

    if(a_imageObject.format() == "P2")
        impl::setBlackAndwhite(a_imageObject, sharpImage, rows - 1, columns - 1, multipliers);
    else
        impl::setColored(a_imageObject, sharpImage, rows - 1, columns - 5, multipliers);

    return sharpImage;
}


}// namespace image

