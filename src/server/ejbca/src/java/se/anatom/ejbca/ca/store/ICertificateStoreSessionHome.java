
package se.anatom.ejbca.ca.store;

import java.rmi.RemoteException;
import javax.ejb.CreateException;
import javax.ejb.EJBHome;


/**
 * @version $Id: ICertificateStoreSessionHome.java,v 1.1 2006/06/09 17:09:07 danijel Exp $
 */
public interface ICertificateStoreSessionHome extends EJBHome {

    /**
     * Default create method. Maps to ejbCreate in implementation.
     * @throws CreateException
     * @throws RemoteException
     * @return ICertificateStoreSessionRemote interface
     */
    ICertificateStoreSessionRemote create() throws CreateException, RemoteException;
}
