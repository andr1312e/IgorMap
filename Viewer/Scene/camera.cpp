#include "camera.h"
#include "camera_p.h"

Camera::Camera( QObject* parent )
    : QObject( parent )
    , d_ptr( new CameraPrivate( this ) )
{
}

Camera::ProjectionType Camera::projectionType() const
{
    Q_D( const Camera );
    return d->m_projectionType;
}

QVector3D Camera::position() const
{
    Q_D( const Camera );
    return d->m_position;
}

void Camera::setPosition( const QVector3D& position )
{
    Q_D( Camera );
    d->m_position = position;
    d->m_cameraToCenter = d->m_viewCenter - position;
    d->m_viewMatrixDirty = true;
}

void Camera::setUpVector( const QVector3D& upVector )
{
    Q_D( Camera );
    d->m_upVector = upVector;
    d->m_viewMatrixDirty = true;
}

QVector3D Camera::upVector() const
{
    Q_D( const Camera );
    return d->m_upVector;
}

void Camera::setViewCenter( const QVector3D& viewCenter )
{
    Q_D( Camera );
    d->m_viewCenter = viewCenter;
    d->m_cameraToCenter = viewCenter - d->m_position;
    d->m_viewMatrixDirty = true;
}

QVector3D Camera::viewCenter() const
{
    Q_D( const Camera );
    return d->m_viewCenter;
}

QVector3D Camera::viewMatrixScale() const
{
    Q_D( const Camera );
    return d->m_viewMatrixScale;
}

QVector3D Camera::viewVector() const
{
    Q_D( const Camera );
    return d->m_cameraToCenter;
}

void Camera::setOrthographicProjection( float left, float right,
                                        float bottom, float top,
                                        float nearPlane, float farPlane )
{
    Q_D( Camera );
    d->m_left = left;
    d->m_right = right;
    d->m_bottom = bottom;
    d->m_top = top;
    d->m_nearPlane = nearPlane;
    d->m_farPlane = farPlane;
    d->m_projectionType = OrthogonalProjection;
    d->updateOrthogonalProjection();
}

void Camera::setPerspectiveProjection( float fieldOfView, float aspectRatio,
                                       float nearPlane, float farPlane )
{
    Q_D( Camera );
    d->m_fieldOfView = fieldOfView;
    d->m_aspectRatio = aspectRatio;
    d->m_nearPlane = nearPlane;
    d->m_farPlane = farPlane;
    d->m_projectionType = PerspectiveProjection;
    d->updatePerpectiveProjection();
}

void Camera::setNearPlane( const float& nearPlane )
{
    Q_D( Camera );
    if ( qFuzzyCompare( d->m_nearPlane, nearPlane ) )
        return;
    d->m_nearPlane = nearPlane;
    if ( d->m_projectionType == PerspectiveProjection )
        d->updatePerpectiveProjection();
}

float Camera::nearPlane() const
{
    Q_D( const Camera );
    return d->m_nearPlane;
}

void Camera::setFarPlane( const float& farPlane )
{
    Q_D( Camera );
    if ( qFuzzyCompare( d->m_farPlane, farPlane ) )
        return;
    d->m_farPlane = farPlane;
    if ( d->m_projectionType == PerspectiveProjection )
        d->updatePerpectiveProjection();
}

float Camera::farPlane() const
{
    Q_D( const Camera );
    return d->m_farPlane;
}

void Camera::setFieldOfView( const float& fieldOfView )
{
    Q_D( Camera );
    if ( qFuzzyCompare( d->m_fieldOfView, fieldOfView ) )
        return;
    d->m_fieldOfView = fieldOfView;
    if ( d->m_projectionType == PerspectiveProjection )
        d->updatePerpectiveProjection();
}

float Camera::fieldOfView() const
{
    Q_D( const Camera );
    return d->m_fieldOfView;
}

void Camera::setAspectRatio( const float& aspectRatio )
{
    Q_D( Camera );
    if ( qFuzzyCompare( d->m_aspectRatio, aspectRatio ) )
        return;
    d->m_aspectRatio = aspectRatio;
    if ( d->m_projectionType == PerspectiveProjection )
        d->updatePerpectiveProjection();
}

float Camera::aspectRatio() const
{
    Q_D( const Camera );
    return d->m_aspectRatio;
}

void Camera::setLeft( const float& left )
{
    Q_D( Camera );
    if ( qFuzzyCompare( d->m_left, left ) )
        return;
    d->m_left = left;
    if ( d->m_projectionType == OrthogonalProjection )
        d->updateOrthogonalProjection();
}

float Camera::left() const
{
    Q_D( const Camera );
    return d->m_left;
}

void Camera::setRight( const float& right )
{
    Q_D( Camera );
    if ( qFuzzyCompare( d->m_right, right ) )
        return;
    d->m_right = right;
    if ( d->m_projectionType == OrthogonalProjection )
        d->updateOrthogonalProjection();
}

float Camera::right() const
{
    Q_D( const Camera );
    return d->m_right;
}

void Camera::setBottom( const float& bottom )
{
    Q_D( Camera );
    if ( qFuzzyCompare( d->m_bottom, bottom ) )
        return;
    d->m_bottom = bottom;
    if ( d->m_projectionType == OrthogonalProjection )
        d->updateOrthogonalProjection();
}

float Camera::bottom() const
{
    Q_D( const Camera );
    return d->m_bottom;
}

void Camera::setTop( const float& top )
{
    Q_D( Camera );
    if ( qFuzzyCompare( d->m_top, top ) )
        return;
    d->m_top = top;
    if ( d->m_projectionType == OrthogonalProjection )
        d->updateOrthogonalProjection();
}

float Camera::top() const
{
    Q_D( const Camera );
    return d->m_top;
}

void Camera::updateScaleOfViewMatrix(const float &factor)
{
    Q_D(Camera);
    //d->m_viewMatrixScale *= factor;
    //if (d->m_viewMatrixScale.x() * factor < 100.) {
        d->m_viewMatrixScale.setX(d->m_viewMatrixScale.x() * factor);
        d->m_viewMatrixScale.setY(d->m_viewMatrixScale.y() * factor);
        //float factorZ = ((factor - 1.) / 2.) + 1.;
        //d->m_viewMatrixScale.setZ(d->m_viewMatrixScale.z() * factorZ);

   // }
    qDebug() << d->m_viewMatrixScale;
}

void Camera::resetScaleOfViewMatrix()
{
    Q_D(Camera);
    d->m_viewMatrixScale = QVector3D(1.,1.,1.);
    emit resetCamera();
    emit translateCamera(d->m_viewCenter);
}

void Camera::viewCenterRequestCamera()
{
    Q_D(Camera);
    emit translateCamera(d->m_viewCenter);
}

QMatrix4x4 Camera::viewMatrix() const
{
    Q_D( const Camera );
    //if ( d->m_viewMatrixDirty )
    //{
        d->m_viewMatrix.setToIdentity();
        d->m_viewMatrix.scale(d->m_viewMatrixScale);
        d->m_viewMatrix.lookAt( d->m_position, d->m_viewCenter, d->m_upVector );
        d->m_viewMatrixDirty = false;
    //}
    return d->m_viewMatrix;
}

QMatrix4x4 Camera::projectionMatrix() const
{
    Q_D( const Camera );
    return d->m_projectionMatrix;
}

QMatrix4x4 Camera::viewProjectionMatrix() const
{
    Q_D( const Camera );
    if ( d->m_viewMatrixDirty || d->m_viewProjectionMatrixDirty )
    {
        d->m_viewProjectionMatrix = d->m_projectionMatrix * viewMatrix();
        d->m_viewProjectionMatrixDirty = false;
    }
    return d->m_viewProjectionMatrix;
}

void Camera::translate( const QVector3D& vLocal, CameraTranslationOption option )
{
    Q_D( Camera );

    // Calculate the amount to move by in world coordinates
    QVector3D vWorld;
    if ( !qFuzzyIsNull( vLocal.x() ) )
    {
        // Calculate the vector for the local x axis
        QVector3D x = QVector3D::crossProduct( d->m_cameraToCenter, d->m_upVector ).normalized();
        vWorld += vLocal.x() * x;
    }

    if ( !qFuzzyIsNull( vLocal.y() ) )
        vWorld += vLocal.y() * d->m_upVector;

    if ( !qFuzzyIsNull( vLocal.z() ) )
        vWorld += vLocal.z() * d->m_cameraToCenter.normalized();

    // Update the camera position using the calculated world vector
    d->m_position += vWorld;

    // May be also update the view center coordinates
    if ( option == TranslateViewCenter )
        d->m_viewCenter += vWorld;

    // Refresh the camera -> view center vector
    d->m_cameraToCenter = d->m_viewCenter - d->m_position;

    // Calculate a new up vector. We do this by:
    // 1) Calculate a new local x-direction vector from the cross product of the new
    //    camera to view center vector and the old up vector.
    // 2) The local x vector is the normal to the plane in which the new up vector
    //    must lay. So we can take the cross product of this normal and the new
    //    x vector. The new normal vector forms the last part of the orthonormal basis
    QVector3D x = QVector3D::crossProduct( d->m_cameraToCenter, d->m_upVector ).normalized();
    d->m_upVector = QVector3D::crossProduct( x, d->m_cameraToCenter ).normalized();

    d->m_viewMatrixDirty = true;

    emit translateCamera(d->m_viewCenter);
}

void Camera::translateWorld(const QVector3D& vWorld , CameraTranslationOption option )
{
    Q_D( Camera );

    // Update the camera position using the calculated world vector
    d->m_position += vWorld;
    //qDebug() << d->m_position;

    // May be also update the view center coordinates
    if ( option == TranslateViewCenter )
        d->m_viewCenter += vWorld;

    // Refresh the camera -> view center vector
    d->m_cameraToCenter = d->m_viewCenter - d->m_position;

    d->m_viewMatrixDirty = true;
}

QQuaternion Camera::pitchRotation( const float& angle ) const
{
    Q_D( const Camera );
    QVector3D xBasis = QVector3D::crossProduct( d->m_upVector, d->m_cameraToCenter.normalized() ).normalized();
    return QQuaternion::fromAxisAndAngle( xBasis, -angle );
}

QQuaternion Camera::yawRotation( const float& angle ) const
{
    Q_D( const Camera );
    return QQuaternion::fromAxisAndAngle( d->m_upVector, angle );
}

QQuaternion Camera::yawRotation( const float& angle, const QVector3D& axis ) const
{
    return QQuaternion::fromAxisAndAngle( axis, angle );
}

QQuaternion Camera::rollRotation( const float& angle ) const
{
    Q_D( const Camera );
    return QQuaternion::fromAxisAndAngle( QVector3D(0.0f, 0.0f, 10.0f), -angle );
    //return QQuaternion::fromAxisAndAngle( d->m_cameraToCenter, -angle );
}

void Camera::pitch( const float& angle )
{
    QQuaternion q = pitchRotation( angle );
    rotate( q );
}

void Camera::yaw( const float& angle )
{
    QQuaternion q = yawRotation( -angle );
    rotate( q );
}

void Camera::yaw( const float& angle, const QVector3D& axis )
{
    QQuaternion q = yawRotation( -angle, axis );
    rotate( q );
}

void Camera::roll( const float& angle )
{
    QQuaternion q = rollRotation( -angle );
    rotate( q );
}

void Camera::pitchAboutViewCenter( const float& angle )
{
    QQuaternion q = pitchRotation( -angle );
    rotateAboutViewCenter( q );
}

void Camera::yawAboutViewCenter( const float& angle )
{
    QQuaternion q = yawRotation( angle );
    rotateAboutViewCenter( q );
}

void Camera::rollAboutViewCenter( const float& angle )
{
    QQuaternion q = rollRotation( angle );
    rotateAboutViewCenter( q );
}

void Camera::rotate( const QQuaternion& q )
{
    Q_D( Camera );
    d->m_upVector = q.rotatedVector( d->m_upVector );
    d->m_cameraToCenter = q.rotatedVector( d->m_cameraToCenter );
    d->m_viewCenter = d->m_position + d->m_cameraToCenter;
}

void Camera::rotateAboutViewCenter( const QQuaternion& q )
{
    Q_D( Camera );
    QVector3D cameraToC = q.rotatedVector( d->m_cameraToCenter );
    qreal angle = QVector3D::dotProduct(QVector3D(0.0f, 0.0f, 10.0f), cameraToC) /
          QVector3D(0.0f, 0.0f, 10.0f).length() * cameraToC.length();
    //qDebug() << angle;
    if (angle > -10)
        return;

    d->m_upVector = q.rotatedVector( d->m_upVector );
    d->m_cameraToCenter = q.rotatedVector( d->m_cameraToCenter );
    d->m_position = d->m_viewCenter - d->m_cameraToCenter;
}
