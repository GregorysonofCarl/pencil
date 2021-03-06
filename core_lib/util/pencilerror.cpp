
#include "pencilerror.h"
#include <map>
#include <QObject>


QString Status::msg()
{
    static std::map<ErrorCode, QString> msgMap =
    {
        // error messages.
        { OK,                    QObject::tr( "Everything ok." ) },
        { FAIL,                  QObject::tr( "Ooops, Something went wrong." ) },
        { FILE_NOT_FOUND,        QObject::tr( "File doesn't exist." ) },
        { ERROR_FILE_CANNOT_OPEN,    QObject::tr( "Cannot open file." ) },
        { ERROR_INVALID_XML_FILE,    QObject::tr( "The file is not a valid xml document." ) },
        { ERROR_INVALID_PENCIL_FILE, QObject::tr( "The file is not valid pencil document." ) },
    };

    auto it = msgMap.find( mCode );
    if ( it == msgMap.end() )
    {
        return msgMap[ FAIL ];
    }
    return msgMap[ mCode ];
}

bool Status::operator==( Status::ErrorCode code )
{
    return ( mCode == code );
}
