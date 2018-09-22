/*    Copyright (c) 2010-2018, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 *
 *    References
 *      Blake, W.B. Missile Datcom User's Manual - 1997 Fortran 90 Version, AFRL-VA-WP-TR-1998-3009
 *          Air Force Research Laboratory, 1998.
 *
 */

#ifndef TUDAT_MISSILE_DATCOM_READER_H
#define TUDAT_MISSILE_DATCOM_READER_H

#include <fstream>
#include <map>
#include <string>
#include <vector>

#include <memory>

namespace tudat
{
namespace input_output
{

//! Class to read a for004.dat file generated by missile Datcom.
/*!
 * Class to read a for004.dat file generated by missile Datcom.
 * Based on the input cards
 * FLC,1,145    (Flight Condition Data)
 * SB1,1,220    (Static Coefficient and Derivative Data)
 * DB1,1,400    (Dynamic Derivative Data)
 */
class MissileDatcomReader
{
public:

    //! Class constructor, reads data file.
    /*!
     * Class constructor, reads data file to vector of doubles containing all data.
     * \param fileNameAndPath Path and name of file containing missile datcom data
     */
    MissileDatcomReader( const std::string& fileNameAndPath );

    //! Gets the split and parsed data from the 004 file
    /*!
     *  Gets the split and parsed data from the 004 file.
     *  \return Vector of doubles, which have been sequentially read from 004 file.
     */
    std::vector< double > getMissileDatcomData( ){ return missileDatcomData_; }

protected:

private:

    //! Function to read the for004.dat file and return one long std::vector
    /*!
     * Function to read the for004.dat file and return one long std::vector
     * with first the FLC data, then the SB1 data, next the DB1 data, and then the
     * same data again for the next machnumber. (see missile datcom user manual p88 and further).
     * \param fileNameAndPath Path and name of the for004.dat file.
     */
    void readFor004( const std::string& fileNameAndPath );

    //! Open data file.
    /*!
     * Opens the for004.dat data file.
     * \param fileNameAndPath Path and name of the for004.dat file.
     */
    void openFile( const std::string& fileNameAndPath );

    //! Function to split a single std::string into a std::vector of std::strings
    /*!
     * Function to split a single std::string into a std::vector of small std::strings.
     * Entries are separated by a separator (which is also a std::string)
     * WARNING: If multiple seperators are placed next to each other, the entry is skipped.
     * \param dataString the long std::string which needs to be splitted.
     * \param separator the separator symbol
     * \param dataVector the std::vector with all the substd::strings.
     */
    void split( const std::string& dataString, char separator,
                std::vector< std::string >& dataVector );

    //! Read and store data.
    /*!
     * Reads and stores data from input file.
     * \param skipKeyword Keyword to skip in input file.
     */
    void readAndStoreData( const std::string& skipKeyword );

    //! Map to store the read for004.dat file.
    /*!
     * Map to store the read for004.dat file.
     */
    std::map< unsigned int, std::string > missileDatcomDataContainer_;

    //! Iterator for std::map container of data from file.
    /*!
     * Iterator for std::map container of std::string data from data file.
     */
    std::map< unsigned int, std::string >::iterator iteratorContainerOfData_;

    //! String to temporarilly store the a splitted std::string.
    /*!
     * String to temporarilly store the a splitted std::string.
     */
    std::vector< std::string > dataVector_;

    //! Data std::vector with the rough split and parsed missileDatcom data.
    /*!
     *  Data std::vector with the rough split and parsed missileDatcom data.
     */
    std::vector< double > missileDatcomData_;

    //! Data file stream.
    /*!
     * Data file stream.
     */
    std::ifstream dataFile_;

    //! Map container of data from file.
    /*!
     * Map container of string data from data file, obtained by reading each
     * line of data from file using the getline( ) function. The key is the
     * line number from the file and the value is line data.
     */
    std::map< unsigned int, std::string > containerOfDataFromFile_;

    //! Function to Convert a string to a double.
    /*!
     * Creates an istringstream object and converted the string to a double. Throws an exception
     * if incorrect string is used.
     * \param inputString string with the data to be converted
     * \return the converted string
     */
    double stringToDouble( std::string const& inputString );
};

//! Typedef for shared-pointer to MissileDatcomReader object.
typedef std::shared_ptr< MissileDatcomReader > MissileDatcomReaderPointer;

} // namespace input_output
} // namespace tudat

#endif // TUDAT_MISSILE_DATCOM_READER_H
