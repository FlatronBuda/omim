#pragma once

#include "qt/qt_common/map_widget.hpp"

#include "map/everywhere_search_params.hpp"
#include "map/place_page_info.hpp"
#include "map/routing_manager.hpp"

#include "search/result.hpp"

#include "routing/router.hpp"

#include "drape_frontend/gui/skin.hpp"

#include "drape_frontend/drape_engine.hpp"

#include <condition_variable>
#include <memory>
#include <mutex>

#include <QtWidgets/QRubberBand>

class Framework;
class QQuickWindow;

namespace qt
{
namespace common
{
class ScaleSlider;
}

class Screenshoter;
struct ScreenshotParams;

class DrawWidget : public qt::common::MapWidget
{
  using TBase = MapWidget;

  Q_OBJECT

public Q_SLOTS:
  void ShowAll();

  void ChoosePositionModeEnable();
  void ChoosePositionModeDisable();
  void OnUpdateCountryStatusByTimer();

public:
  DrawWidget(Framework & framework, bool apiOpenGLES3, std::unique_ptr<ScreenshotParams> && screenshotParams,
             QWidget * parent);
  ~DrawWidget() override;

  bool Search(search::EverywhereSearchParams const & params);
  string GetDistance(search::Result const & res) const;
  void ShowSearchResult(search::Result const & res);

  void CreateFeature();

  void OnLocationUpdate(location::GpsInfo const & info);

  void UpdateAfterSettingsChanged();

  void PrepareShutdown();

  Framework & GetFramework() { return m_framework; }

  void SetMapStyle(MapStyle mapStyle);

  void SetRouter(routing::RouterType routerType);

  using TCurrentCountryChanged = function<void(storage::CountryId const &, string const &,
                                               storage::Status, uint64_t, uint8_t)>;
  void SetCurrentCountryChangedListener(TCurrentCountryChanged const & listener);

  void DownloadCountry(storage::CountryId const & countryId);
  void RetryToDownloadCountry(storage::CountryId const & countryId);

  void SetSelectionMode(bool mode);
  void SetCityBoundariesSelectionMode(bool mode);
  void SetCityRoadsSelectionMode(bool mode);

  RouteMarkType GetRoutePointAddMode() const { return m_routePointAddMode; }
  void SetRoutePointAddMode(RouteMarkType mode) { m_routePointAddMode = mode; }
  void FollowRoute();
  void ClearRoute();
  void OnRouteRecommendation(RoutingManager::Recommendation recommendation);

  void RefreshDrawingRules();

  static void SetDefaultSurfaceFormat(bool apiOpenGLES3);

protected:
  /// @name Overriden from MapWidget.
  //@{
  void initializeGL() override;

  void mousePressEvent(QMouseEvent * e) override;
  void mouseMoveEvent(QMouseEvent * e) override;
  void mouseReleaseEvent(QMouseEvent * e) override;
  void keyPressEvent(QKeyEvent * e) override;
  void keyReleaseEvent(QKeyEvent * e) override;

  void OnViewportChanged(ScreenBase const & screen) override;
  //@}
private:
  void SubmitFakeLocationPoint(m2::PointD const & pt);
  void SubmitRoutingPoint(m2::PointD const & pt);
  void SubmitBookmark(m2::PointD const & pt);
  void ShowPlacePage(place_page::Info const & info);

  void UpdateCountryStatus(storage::CountryId const & countryId);

  m2::PointD GetCoordsFromSettingsIfExists(bool start, m2::PointD const & pt);

  QRubberBand * m_rubberBand;
  QPoint m_rubberBandOrigin;

  bool m_emulatingLocation;

  TCurrentCountryChanged m_currentCountryChanged;
  storage::CountryId m_countryId;

  bool m_selectionMode = false;
  bool m_cityBoundariesSelectionMode = false;
  bool m_cityRoadsSelectionMode = false;
  RouteMarkType m_routePointAddMode = RouteMarkType::Finish;

  std::unique_ptr<Screenshoter> m_screenshoter;
};
}  // namespace qt
