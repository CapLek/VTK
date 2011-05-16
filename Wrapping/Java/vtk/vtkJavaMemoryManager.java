package vtk;

/**
 * This interface provide all the methods needed for the management of vtkObject
 * in the Java world. They are used internally inside the generated Java code of
 * the VTK objects to keep track of the reference count of the corresponding VTK
 * C++ object and therefore allow to release memory when it became possible.
 *
 * Only the 3 following methods should be called by the user: - gc(boolean) : to
 * run the garbage collection - getAutoGarbageCollector() : to get the EDT
 * garbage collection scheduler - deleteAll() : to free any remaining VTK
 * object.
 *
 * @author sebastien jourdain - sebastien.jourdain@kitware.com
 */
public interface vtkJavaMemoryManager {
    /**
     * Create or return an existing instance of the vtkObject that corresponds
     * to the pointer id vtkId.
     *
     * @param <T>
     *            Type of the object that we want to return.
     * @param className
     *            Concreate class that should be created if needed.
     * @param vtkId
     *            is used to uniquely identify a vtkObject inside the C++ layer.
     *
     * @return a java object that map its underlying C++ instance.
     */
    <T extends vtkObjectBase> T getJavaObject(String className, Long vtkId);

    /**
     * Store the Java instance of a vtkObject inside a weak pointer map.
     *
     * @param id
     *            is used to uniquely identify a vtkObject inside the C++ layer.
     * @param obj
     *            is the Java instance that is stored inside a WeakPointer of
     *            the map.
     */
    void registerJavaObject(Long id, vtkObjectBase obj);

    /**
     * If found the Java object is removed from the map and we decrease the
     * reference count of the underneath C++ instance.
     *
     * @param id
     */
    void unRegisterJavaObject(Long id);

    /**
     * Execute the garbage collection in the Java + VTK context to release Java
     * instance that are not used anymore which keep holding a C++ instance
     * around.
     *
     * @param debug
     *            allow to add extra information inside the return object such
     *            as the class name of the objects lefts as well as their
     *            numbers.
     *
     * @return an information object that provide useful informations for
     *         statistic or debuging purpose.
     */
    vtkReferenceInformations gc(boolean debug);

    /**
     * @return an helper class that allow to trigger the garbage collector at a
     *         given frequency inside the EDT.
     */
    vtkJavaGarbageCollector getAutoGarbageCollector();

    /**
     * This method will clean up the Map of the Java objects and will release
     * any vtkObject that was held by a Java one. This will prevent you from
     * using any existing VTK Java object.
     *
     * @return the size of the map that we cleared
     */
    int deleteAll();

    /**
     * @return the number of vtkObject that are currently used inside the Java
     *         world.
     */
    int getSize();
}
