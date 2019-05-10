import Tudat as ptd

class bodyInterfaceObject:

    def __init__(self, propagationWrapperObject, name):
        self.bodyName = name
        self.propagationWrapperObject = propagationWrapperObject
        self.accelerationMap = {}

    def setName(self, newName):
        self.bodyName = newName
        return self  # Monadic composition


    def addAcceleration(self, exertingBodyName, accelerationType):
        if exertingBodyName in self.accelerationMap.keys():
            self.accelerationMap[exertingBodyName].append(accelerationType)
        else:
            self.accelerationMap[exertingBodyName] = [accelerationType]
        return self




class PropagationHelper:



    def __init__(self):
        self.bodyMap = ptd.NamedBodyMap()
        self.bodyInterfaceObjects = []
        self.accelMap = ptd.FullAccelerationMap()

    def populateWithCommonlyUsedBodies(self, bodiesNameList):
        """
        Create commonly used bodies, like the Earth or Mars, with appropriate, pre-computed settings. This erases existing
        bodies defined before the call.
        :param bodiesNameList: Names of the common bodies
        """
        settingsMap = ptd.getDefaultBodySettingsMap(bodiesNameList)

        self.bodyMap = ptd.createBodies(settingsMap)
        ptd.setGlobalFrameBodyEphemerides(self.bodyMap, "SSB", "ECLIPJ2000")


    def createBody(self, name):
        ifaceObject = bodyInterfaceObject(self, name)
        self.bodyInterfaceObjects.append(ifaceObject)
        return ifaceObject

    def setupPropagation(self,propagatedBodiesList,centralBodiesList):
        # Get the settings back to the bodyInterfaceObjects
        for bodyIface in self.bodyInterfaceObjects:
            self.bodyMap[bodyIface.bodyName] = ptd.Body()
            accelSettingsForBody = ptd.PerBodyAccelerationSettings()
            for key, value in bodyIface.accelerationMap.items():
                accelSettingsForBody.addAcceleration(exertingBodyName=key, listOfAccelerationSettings=value)
            self.accelMap[bodyIface.bodyName] = accelSettingsForBody

        self.modelAccelerationMap = ptd.createAccelerationModelsMap(bodyMap=self.bodyMap,
                                                               fullAccelerationMap=self.accelMap,
                                                               propagatedBodiesList=propagatedBodiesList,
                                                               centralBodiesList=centralBodiesList)




