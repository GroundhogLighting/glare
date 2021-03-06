/*****************************************************************************
	Emp

    Copyright (C) 2018  German Molina (germolinal@gmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*****************************************************************************/


#pragma once

#include <string>
#include "./weather.h"

//! Represents a Location

/*!
This object contains the information required to place the sun somewhere
*/

class Location {
private: 
	float latitude; //!< The latitude in degrees North (use negative for South)
	float longitude; //!< The longitude in degrees West (use negative for East)
	float timeZone; //!< in GMT units
	std::string city; //!< The name of the city
	std::string country; //!< The name of the country
	float albedo = 0.2f; //!< The albedo in the location
	Weather weather = Weather(); //!< The weather of the location obtained from a weather file
	float elevation = 0; //!< The elevation

public:
	
	//! Creates a new Location object
	/*!
	Both City Name and Country Name are set to 'not specified'. The Latitude, 
	Longitude and Time Zone are set to 0.

	@author German Molina	
	*/
	Location();
		

	//! Retrieves the latitude
	/*!
	@author German Molina
	@return the latitude
	*/
	float getLatitude() const;

	//! Sets the latitude
	/*!
	@author German Molina
	@param[in] l The latitude
	*/
	void setLatitude(float l);
	
	//! Retrieves the longitude
	/*!
	@author German Molina
	@return the longitude
	*/
	float getLongitude() const;

	//! Sets the Longitude
	/*!
	@author German Molina
	@param[in] l The longitude
	*/
	void setLongitude(float l);
	
	//! Retrieves the Time Zone
	/*!
	@author German Molina
	@return the time zone
	*/
	float getTimeZone() const;

	//! Sets the Time zone
	/*!
	@author German Molina
	@param[in] t The time zone
	*/
	void setTimeZone(float t);
	
	//! Retrieves the City name
	/*!
	@author German Molina
	@return the city name
	*/
	std::string getCity() const;

	//! Sets the City name
	/*!
	@author German Molina
	@param[in] c The city name
	*/
	void setCity(std::string c);
	
	//! Retrieves the Country name
	/*!
	@author German Molina
	@return the country name
	*/
	std::string getCountry() const;

	//! Sets the Country name
	/*!
	@author German Molina
	@param[in] c The country name
	*/
	void setCountry(std::string c);

	//! Sets the albedo
	/*!
	@author German Molina
	@param[in] a The albedo
	*/
	void setAlbedo(float a);

	//! Gets the albedo
	/*!
	@author German Molina
	@return The albedo
	*/
	float getAlbedo() const;

	//! Fill Weather member from JSON object
	/*!
	@author German Molina
	@param[in] j The JSON object
	@return success
	*/
	bool fillWeatherFromJSON(json * j);

    //! Loads an EPW file into the weather.
    /*!
     @author German Molina
     @param filename [String] The name of the file to read
     @return success
     */
    bool fillWeatherFromEPWFile(std::string filename);
    
    //! Loads an WEA file into the weather.
    /*!
     @author German Molina
     @param filename [String] The name of the file to read
     @return success
     */
    bool fillWeatherFromWEAFile(std::string filename);
    
	//! Gets the elevation
	/*!
	@author German Molina
	@return The elevation
	*/
	float getElevation() const;

    //! Sets the elevation
    /*!
     @author German Molina
     @param[in] a The elevation
     */
    void setElevation(float a);
    
	//! Gets the HourlyData for some hour
	/*!
	@author German Molina
	@param[in] hour The hour of the year
	@return The data
	*/
	HourlyData * getHourlyData(size_t hour);
    
    //! Add hourly data
    /*!
     @author German Molina
     @param h The hourly data to add
     */
    void addHourlyData(HourlyData h);
    
    //! Gets the number of samples in the weather data
    /*!
     @author German Molina
     @return The weather data length
     */
    size_t getWeatherSize() const;

	//! Checks if the weather has been filled with data
	/*!
	@author German Molina
	*/
	bool hasWeather() const;
    
    //! Marks weather as filled
    /*!
     @author German Molina
     */
    void markWeatherAsFilled();
    
    //! Interpolats the weather data
    /*!
     @author German Molina
     @param step The starting measured point     
     @param i The scheme to interpolate (0 to 1)
     @param data The HourlyData object to put the results in
     @todo Consider interpolation at sunrise and sunset!
     */
    void getInterpolatedData(int step,float i,HourlyData * data) const;
    
    
    //! Retrieves weather data by date and time
    /*!
     @author German Molina
     @param month The month
     @param day The day
     @param hour The hour
     */
    void getDataByDate(int month, int day, float time, HourlyData * data) const;
};
