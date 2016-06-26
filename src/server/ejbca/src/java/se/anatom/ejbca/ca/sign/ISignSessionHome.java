
package se.anatom.ejbca.ca.sign;

import java.rmi.RemoteException;
import javax.ejb.CreateException;
import javax.ejb.EJBHome;


/**
 * @version $Id: ISignSessionHome.java,v 1.1 2006/06/09 17:09:06 danijel Exp $
 */
public interface ISignSessionHome extends EJBHome {

    /**
     * Default create method. Maps to ejbCreate in implementation.
     * @throws CreateException
     * @throws RemoteException
     * @return ISignSessionRemote interface
     */
    ISignSessionRemote create() throws CreateException, RemoteException;
}
