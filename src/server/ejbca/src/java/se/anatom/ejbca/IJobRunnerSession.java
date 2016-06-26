
package se.anatom.ejbca;

import java.util.*;
import java.rmi.RemoteException;

/**
 * JobRunner session wraps around any class and is a general session bean
 * that can be used to launch a specified job.
 *
 * @version $Id: IJobRunnerSession.java,v 1.1 2006/06/09 17:09:06 danijel Exp $
 */
public interface IJobRunnerSession {
    public void run() throws RemoteException;
}
