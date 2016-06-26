
package se.anatom.ejbca.ca.store;

import java.rmi.RemoteException;
import javax.ejb.CreateException;
import javax.ejb.EJBHome;


/**
 * @version $Id: IPublisherSessionHome.java,v 1.1 2006/06/09 17:09:07 danijel Exp $
 */
public interface IPublisherSessionHome extends EJBHome {

    /**
     * Default create method. Maps to ejbCreate in implementation.
     * @throws CreateException
     * @throws RemoteException
     * @return IPublisherSessionRemote interface
     */
    IPublisherSessionRemote create() throws CreateException, RemoteException;
}
