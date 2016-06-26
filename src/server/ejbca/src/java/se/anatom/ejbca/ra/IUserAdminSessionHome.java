
package se.anatom.ejbca.ra;

import java.rmi.RemoteException;
import javax.ejb.CreateException;
import javax.ejb.EJBHome;


/**
 * @version $Id: IUserAdminSessionHome.java,v 1.1 2006/06/09 17:09:07 danijel Exp $
 */
public interface IUserAdminSessionHome extends EJBHome {

    /**
     * Default create method. Maps to ejbCreate in implementation.
     * @throws CreateException
     * @throws RemoteException
     * @return IUserAdminSessionRemote interface
     */
    IUserAdminSessionRemote create() throws CreateException, RemoteException;
}
