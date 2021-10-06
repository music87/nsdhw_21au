#include<cstddef>
#include<iostream>
#include <algorithm>
#include<vector>
using namespace std;

class Line
{
public:
    Line() {} //basic constructor
    Line(Line const & other) {
        //copy constructor
        m_coords.resize(other.m_coords.size(), 0);
        m_coords.assign(other.m_coords.begin(), other.m_coords.end());
    }
    Line(Line && other) : m_coords(other.m_coords.size(),0) { 
        //move constructor
        //another writing style (colon) using the fill constructor of vector in STL container
        m_coords.assign(other.m_coords.begin(), other.m_coords.end());
        other.m_coords.clear();
    }   
    Line & operator=(Line const & other){  
        //copy assignment operator
	if (this == &other) {return *this;}
	m_coords.resize(other.m_coords.size(), 0);
        m_coords.assign(other.m_coords.begin(), other.m_coords.end());
	return *this;
    } 
    Line & operator=(Line       && other){ 
        //move assignment operator
        if (this == &other) {return *this;}      
        m_coords.resize(other.m_coords.size(), 0);
	m_coords.assign(other.m_coords.begin(), other.m_coords.end());
        other.m_coords.clear();
	return *this;
    }
    Line(size_t size) : m_coords(size*2, 0) {}//custom constructor; size means the number of points, and there are two coordinates for each points.  
    ~Line() {}//destructor
    // accessors
    size_t size() const{ return m_coords.size()/2; }
    float x(size_t it) const{ return m_coords.at(it*2); } //vector.at() will automatically check the vector's boundary
    float & x(size_t it){ return m_coords.at(it*2); }
    float y(size_t it) const{ return m_coords.at(it*2+1); }
    float & y(size_t it){ return m_coords.at(it*2+1); }
private:
    // Member data.
    vector<float> m_coords; 
}; /* end class Line */


int main(int, char **)
{
    Line line(3);
    line.x(0) = 0; line.y(0) = 1;
    line.x(1) = 1; line.y(1) = 3;
    line.x(2) = 2; line.y(2) = 5;
    
    Line line2(line);
    line2.x(0) = 9;
    
    cout << "line: number of points = " << line.size() << endl;
    for (size_t it=0; it<line.size(); ++it)
    {
        cout << "point " << it << ":"
	     << " x = " << line.x(it)
	     << " y = " << line.y(it) << endl;
    }

    cout << "line2: number of points = " << line.size() << endl;
    for (size_t it=0; it<line.size(); ++it)
    {
        cout << "point " << it << ":"
	     << " x = " << line2.x(it)
	     << " y = " << line2.y(it) << endl;
    }
    
    return 0;

}

