#include "object.h"
#include "test_layermanager.h"


void TestLayerManager::initTestCase()
{
    m_pObject = new Object();
    m_pObject->defaultInitialisation();
}

void TestLayerManager::cleanupTestCase()
{
}