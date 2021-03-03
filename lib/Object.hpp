//
// Created by brucknem on 22.02.21.
//

#ifndef OPENDRIVE_OBJECT_H
#define OPENDRIVE_OBJECT_H

#include <string>
#include <memory>
#include "standard/OpenDRIVE_1.4H_Schema_Files.hxx"
#include "OpenDriveWrapper.hpp"

namespace opendrive {

    /**
     * Wrapper for the OpenDRIVE object class.
     * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_objects
     */
    class Object : public OpenDriveWrapperWithCoordinate<object> {

    public:

        /**
         * @constructor
         */
        explicit Object() = default;

        /**
         * @constructor
         */
        explicit Object(const class object &openDriveObject);

        /**
         * @destructor
         */
        ~Object() override = default;

        /**
         * @get The t-coordinate of object’s origin.
         */
        double getTCoordinate() const;

        /**
         * @get Type of object.
         */
        std::string getType() const;

        /**
         * @get Name of the object.
         */
        std::string getName() const;

        /**
         * @get Id of the object.
         */
        std::string getId() const;

        /**
         * @operator
         */
        friend std::ostream &operator<<(std::ostream &os, const Object &other);
    };
}

#endif //OPENDRIVE_OBJECT_H
