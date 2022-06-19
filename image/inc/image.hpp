#pragma once

namespace image
{

template<typename T>  
class Image
{
public:
    Image(size_t a_rows = 1, size_t a_columns = 1, std::string a_format = "P2", int a_colorScale = 255);
    Image(Image const& a_source);
    Image(Image&& a_source);
    Image& operator=(Image const& a_source);
    Image<T>& operator=(Image<T>&& a_source);
    ~Image();
   
    T getPixel(size_t a_rows, size_t a_columns) const;
    void setPixel(size_t  a_rows, size_t a_columns, T a_value);
    void swap(Image<T>& a_source);

    void setScale(int a_colorScale);

    size_t rows()const;
    size_t columns()const;
    T scale()const;
    std::string format()const;

    bool operator==(Image const& a_source);

private:
    size_t m_rows;
    size_t m_columns;
    std::string m_format;
    T m_colorScale;
    T* m_pixels;
};

template<typename T>  
Image<T> read (std::ifstream& a_imageFile);

template<typename T>  
void save (Image<T>& a_imageObject, std::ofstream& a_imagefile);

template<typename T>  
void brighten (Image<T>& a_imageObject, int a_factor = 20);

template<typename T> 
void changeColorScale(Image<T>& a_imageObject, T a_scale = 4);

template<typename T> 
void reducePixels(Image<T>& a_imageObject, int a_by = 2);


} // namespace image

#include "./inl/image.hxx"
